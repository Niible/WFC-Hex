#include "OverlappingModel.h"

#include <cassert>
#include <unordered_map>

#include "Utils/Utils.h"

OverlappingModel::OverlappingModel(
	const std::vector<std::vector<int>>& input_model_datas,
	const std::vector<MapSize>& input_model_sizes,
	const int symmetry,
	const int n, 
	const MapSize& output_map_size
	)
	: Model(n, output_map_size)
{
	assert(input_model_datas.size() == input_model_sizes.size());
	// change for uint
	/*
	 * The Data representation with the colors indexes
	 */
	std::vector<std::vector<int>> samples;
	samples.resize(input_model_datas.size());

	colors.reserve(10);

	for (auto i = 0; i < input_model_datas.size(); ++i)
	{
		const auto& input_data = input_model_datas[i];
		samples[i].reserve(input_data.size());
		for (int color : input_data)
		{
			auto k = 0;
			for (; k < colors.size(); ++k)
			{
				if (colors[k] == color) break;
			}
			if (k == colors.size())
			{
				colors.push_back(color);
			}
			samples[i].push_back(k);
		}
	}

	/*
	 * Store an hash of the pattern N*N and the Index in
	 * the weights vector witch contains the occurrence of the pattern
	 */
	std::unordered_map<long long, int> pattern_indices;

	// Number of different colors
	const int number_of_colors = static_cast<int>(colors.size());

	for (auto i = 0; i < samples.size(); ++i) {
		const auto& sample = samples[i];
		const auto& [width, height] = input_model_sizes[i];
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				OddrCoordinates CurrentHex = { x, y };
				std::vector<std::vector<int>> ps;
				ps.resize(symmetry, std::vector<int>(GetPatternSize(n)));

				const auto isPatternValid = GetHexPatternFromOddr(sample, input_model_sizes[i], CurrentHex, n, ps[0]);

				if (!isPatternValid) continue;

				if (symmetry > 1)
					ReflectHexPattern(ps[0], CurrentHex, n, ps[1]);
				if (symmetry > 2)
					RotateHexPattern(ps[0], CurrentHex, n, ps[2]);
				if (symmetry > 3)
					ReflectHexPattern(ps[2], CurrentHex, n, ps[3]);
				if (symmetry > 4)
					RotateHexPattern(ps[2], CurrentHex, n, ps[4]);
				if (symmetry > 5)
					ReflectHexPattern(ps[4], CurrentHex, n, ps[5]);
				if (symmetry > 6)
					RotateHexPattern(ps[4], CurrentHex, n, ps[6]);
				if (symmetry > 7)
					ReflectHexPattern(ps[6], CurrentHex, n, ps[7]);
				if (symmetry > 8)
					RotateHexPattern(ps[6], CurrentHex, n, ps[8]);
				if (symmetry > 9)
					ReflectHexPattern(ps[8], CurrentHex, n, ps[9]);
				if (symmetry > 10)
					RotateHexPattern(ps[8], CurrentHex, n, ps[10]);
				if (symmetry > 11)
					ReflectHexPattern(ps[10], CurrentHex, n, ps[11]);

				for (int k = 0; k < symmetry; k++)
				{
					long long h = Hash(ps[k], number_of_colors);
					auto pattern_indices_iterator = pattern_indices.find(h);
					if (pattern_indices_iterator != pattern_indices.end())
					{
						const int index = pattern_indices_iterator->second;
						weights[index] = weights[index] + 1;
					}
					else
					{
						// @todo reserve place for wwight and patterns before all
						pattern_indices.emplace(h, weights.size());
						weights.push_back(1.0);
						patterns.push_back(ps[k]);
					}
				}
			}
		}
	}

	// remove the T maybe
	T = static_cast<int>(weights.size());

	propagator = std::vector(NumberOfNeighbors, std::vector<std::vector<int>>(T));

	InitCellInfo(T);

	std::vector<int> list;
	list.reserve(T);

	constexpr CubeHexCoordinates center_hex = { 0, 0 };
	std::vector<CubeHexCoordinates> neighbors(GetPatternSize(n));
	GetNeighborsCubeCoordinatesInRadius(center_hex, n, neighbors);

	std::vector<int> Indexes(GetTranslationArraySize(n));
	ComputeTranslationIndexesForN(n, Indexes);

	std::vector<int> RotatedIndexes(GetPatternSize(n));
	std::vector<int> TranslatedIndexes(GetPatternSize(n));


	// @todo create function for initialisation of RotatedIndexes and TranslatedIndexes
	for (int d = 0; d < NumberOfNeighbors; d++)
	{
		auto rotatedNeighbors{ neighbors };

		// Can we rotate all 6 neighbors at the same time ? for optimization
		for (int i = 0; i < neighbors.size(); ++i) {
			RotateCubeClockwise(rotatedNeighbors[i], d);
		}

		for (auto i = 0; i < neighbors.size(); ++i)
		{
			const auto& neighbor = neighbors[i];
			for (auto j = 0; j < rotatedNeighbors.size(); ++j)
			{
				const auto& rotated_neighbor = rotatedNeighbors[j];
				if (neighbor == rotated_neighbor) {
					RotatedIndexes[i] = j;
					break;
				}
			}
		}


		for (int i = 0; i < neighbors.size(); ++i) {
			const CubeHexCoordinates hex = neighbors[i];
			const CubeHexCoordinates translatedCoordinates = { hex.q + 1, hex.r };

			for (int j = 0; j < rotatedNeighbors.size(); ++j)
			{
				const auto& rotated_neighbor = rotatedNeighbors[j];
				if (rotated_neighbor == translatedCoordinates) {
					TranslatedIndexes[i] = j;
					break;
				}
			}
		}

		for (int t = 0; t < T; t++)
		{
			list.clear();
			for (int t2 = 0; t2 < T; t2++)
			{
				if (Agrees(patterns[t], patterns[t2], Indexes, RotatedIndexes, TranslatedIndexes))
				{
					list.push_back(t2);
				}
			}
	//		cellInfos[t].propagator[d] = list;
			propagator[d][t] = list;
		}
	}
}


bool OverlappingModel::Save(std::vector<int>& output_datas)
{
	const auto [output_width, output_height] = output_size;
	output_datas.resize(output_width * output_height);
	const int pattern_index = patterns[0].size() / 2;
	if (cellInfos[0].observed >= 0)
	{
		for (auto y = 0; y < output_height; y++)
		{
			//const int dy = y < output_height - n + 1 ? 0 : n - 1;
			for (auto x = 0; x < output_width; x++)
			{
				//const int dx = x < output_width - n + 1 ? 0 : n - 1;
				//const int observed_index = x - dx + (y - dy) * output_width;
				const int observed_index = x + y  * output_width;
				//const int pattern_index = dx + dy * n;
				//const int pattern_index = 0;

				const int observe = cellInfos[observed_index].observed;
				if (observe == -1) return false;
				output_datas[x + y * output_width] = colors[patterns[observe][pattern_index]];
			}
		}
		return true;
	}
	return false;
}