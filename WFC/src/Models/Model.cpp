#include "Model.h"

#include "Config.h"
#include "Utils/HexGridUtils.h"
#include "Utils/Random.h"

#include <complex>


void Model::Init()
{
	distribution = std::vector<double>(T);

	weightLogWeights = std::vector<double>(T);

	double sumOfWeights = 0;
	double sumOfWeightLogWeights = 0;
	for (int t = 0; t < T; t++)
	{
		weightLogWeights[t] = weights[t] * std::log(weights[t]);
		sumOfWeights += weights[t];
		sumOfWeightLogWeights += weightLogWeights[t];
	}

	const double startingEntropy = std::log(sumOfWeights) - sumOfWeightLogWeights / sumOfWeights;

	stack = std::vector<std::pair<int, int>>{ static_cast<size_t>(output_size.width * output_size.height * T) };
	stacksize = 0;

	InitCellEntropies(startingEntropy, sumOfWeights, sumOfWeightLogWeights);

}

bool Model::Run(const int limit)
{
	Init();
	Clear();

	for (int l = 0; l < limit || limit < 0; l++)
	{
		const int node = NextUnobservedNode();
		if (node >= 0)
		{
			Observe(node);
			const bool success = Propagate();
			if (!success)
			{
				return false;
			}
		}
		else
		{
			for (int i = 0; i < output_size.width * output_size.height; i++)
			{
				auto& cell = cellInfos[i];
				for (int t = 0; t < T; t++)
				{
					if (cell.wave[t])
					{
						cell.observed = t;
						break;
					}
				}
			}

			return true;
		}
	}

	return true;
}



int Model::NextUnobservedNode()
{
	double min = 1E+4;
	int node_index = -1;
	for (int i = 0; i < cellInfos.size(); i++)
	{
		auto& cell = cellInfos[i];
		if constexpr (!periodic) {
			if (i % output_size.width + n > output_size.width || i / output_size.width + n > output_size.height)
			{
				continue;
			}
		}
		if (cell.sumsOfOnes > 1 && cell.entropies <= min)
		{
			const double r = RandDouble();
			const double noise = 1E-6 * r;
			if (cell.entropies + noise < min)
			{
				min = cell.entropies + noise;
				node_index = i;
			}
		}
	}

	return node_index;
}


void Model::Observe(const int node)
{
	auto& cell = cellInfos[node];
	std::vector<bool>& w = cell.wave;
	for (int t = 0; t < T; t++)
	{
		distribution[t] = w[t] ? weights[t] : 0.0;
	}
	const int r = RandomWeight(distribution);
	for (int t = 0; t < T; t++)
	{
		if (w[t] != (t == r))
		{
			Ban(node, t);
		}
	}
}


bool Model::Propagate()
{
	while (stacksize > 0)
	{
		auto [i1, t1] = stack[stacksize - 1];
		stacksize--;

		const OddrCoordinates cell_coordinates = GetGridCoordinatesForIndex(i1, output_size.width);
		const CubeHexCoordinates cell_cube_coordinates = GetCubeCoordinatesFromOddr(cell_coordinates);
		static std::array<CubeHexCoordinates, NumberOfNeighbors> neighbors{};
		GetCubeNeighbors(cell_cube_coordinates, neighbors);

		for (int d = 0; d < NumberOfNeighbors; d++)
		{
			const auto neighbor = neighbors[d];
			const OddrCoordinates neighbor_coordinates = GetOddrCoordinatesFromCube(neighbor);
			int x2, y2;
			if constexpr (periodic)
			{
				x2 = neighbor_coordinates.x % output_size.width;
				y2 = neighbor_coordinates.y % output_size.height;

				x2 += (x2 >> 31) & output_size.width;
				y2 += (y2 >> 31) & output_size.height;

			} else {
				x2 = neighbor_coordinates.x;
				y2 = neighbor_coordinates.y;
				if (x2 < 0 || y2 < 0 || x2 + n > output_size.width || y2 + n > output_size.height)
				{
					continue;
				}
			}

			const int neighbor_index = x2 + y2 * output_size.width;
			auto& cell = cellInfos[neighbor_index];

			for (int l = 0; l < propagator[d][t1].size(); l++)
			{
				const int t2 = propagator[d][t1][l];

				--cell.compatible[d][t2];
				if (cell.compatible[d][t2] == 0)
				{
					Ban(neighbor_index, t2);
				}
			}
			

			/*for (int l = 0; l < cellInfos[t1].propagator[d].size(); l++)
			{
				const int t2 = cellInfos[t1].propagator[d][l];

				--cell.compatible[d][t2];
				if (cell.compatible[d][t2] == 0)
				{
					Ban(neighbor_index, t2);
				}
			}*/
		}
	}

	return cellInfos[0].sumsOfOnes > 0;
}


void Model::Ban(int i, int t)
{
	auto& cell = cellInfos[i];
	cell.wave[t] = false;

	for (int d = 0; d < NumberOfNeighbors; d++)
	{

		cell.compatible[d][t] = 0;
	}
	stack[stacksize] = std::pair<int, int>(i, t);
	stacksize++;

	cell.sumsOfOnes -= 1;
	cell.sumOfWeights -= weights[t];
	cell.sumOfWeightLogWeights -= weightLogWeights[t];

	const double sum = cell.sumOfWeights;
	cell.entropies = std::log(sum) - cell.sumOfWeightLogWeights / sum;
}

void Model::InitCellInfo(int t)
{
	cellInfos = std::vector<CellInfo>(output_size.width * output_size.height);
	for (int i = 0; i < output_size.width * output_size.height; ++i)
	{
		cellInfos[i].Init(t);
	}
}

void Model::InitCellEntropies(double startingEntropy, double sumOfWeights, double sumOfWeightLogWeights)
{
	for (int i = 0; i < output_size.width * output_size.height; ++i)
	{
		cellInfos[i].InitEntropy(startingEntropy, sumOfWeights, sumOfWeightLogWeights);
	}
}


void Model::Clear()
{
	for (int i = 0; i < cellInfos.size(); ++i)
	{
		auto& cellInfo = cellInfos[i];
		cellInfo.Reset(T);

		for (int d = 0; d < NumberOfNeighbors; d++) {
			for (int t = 0; t < T; t++)
			{
				cellInfo.compatible[d][t] = propagator[opposite[d]][t].size();
			}
		}
	}
	observedSoFar = 0;
}

std::array<int, NumberOfNeighbors> Model::dx = { -1, -1, -1, 0, 0, 0 };
std::array<int, NumberOfNeighbors> Model::dy = { 0, 1, -1, 1, 0, -1 };
std::array<int, NumberOfNeighbors> Model::opposite = { 3, 4, 5, 0, 1, 2 };