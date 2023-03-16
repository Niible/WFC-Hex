#pragma once

#include "HexGridUtils.h"
#include "../Config.h"

template<typename T>
inline int GetIndex(std::vector<T>& arr, T& val)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i] == val) return i;
	}
	return -1;
}



template<typename T>
bool GetHexPatternFromOddr(const std::vector<T>& sample, const MapSize& sample_size, const OddrCoordinates& oddr_coordinates, const int radius, std::vector<T>& result)
{
	const CubeHexCoordinates cube_hex_coordinates = GetCubeCoordinatesFromOddr(oddr_coordinates);
	std::vector<CubeHexCoordinates> neighbors(GetPatternSize(radius));
	GetNeighborsCubeCoordinatesInRadius(cube_hex_coordinates, radius, neighbors);
	for (int i = 0; i < neighbors.size(); ++i)
	{
		const auto neighbor_oddr_coordinate = GetOddrCoordinatesFromCube(neighbors[i]);
		const auto sample_index = GetIndexForOddrCoordinates(neighbor_oddr_coordinate, sample_size.width, sample_size.height);
		if (sample_index == -1) return false;
		result[i] = sample[sample_index];
	}
	return true;
}

template<typename T>
void RotateHexPattern(const std::vector<T>& base, const OddrCoordinates oddr_coordinates, const int radius, std::vector<T>& result)
{
	static auto pattern_size = GetPatternSize(radius);
	const CubeHexCoordinates currentCubeHex = GetCubeCoordinatesFromOddr(oddr_coordinates);
	static std::vector<CubeHexCoordinates> neighbors(pattern_size);
	static std::vector<CubeHexCoordinates> rotated_neighbors(pattern_size);
	GetNeighborsCubeCoordinatesInRadius(currentCubeHex, radius, neighbors);
	result = base;
	for (int i = 0; i < pattern_size; ++i)
	{
		RotateCubeClockwise(neighbors[i], currentCubeHex, rotated_neighbors[i]);

		int index = GetIndex(neighbors, rotated_neighbors[i]);

		result[index] = base[i];
	}
}

template<typename T>
void ReflectHexPattern(const std::vector<T>& base, const OddrCoordinates oddr_coordinates, const int radius, std::vector<T>& result)
{
	const CubeHexCoordinates cube_hex_coordinates = GetCubeCoordinatesFromOddr(oddr_coordinates);
	static std::vector<CubeHexCoordinates> neighbors(GetPatternSize(radius));
	GetNeighborsCubeCoordinatesInRadius(cube_hex_coordinates, radius, neighbors);
	for (int i = 0; i < neighbors.size(); ++i)
	{
		auto reflected_node = ReflectSCube(neighbors[i], cube_hex_coordinates);

		int index = GetIndex(neighbors, reflected_node);

		result[index] = base[i];
	}
}

/*
 * return a hash of the pattern and return as a long long
 */
inline long long Hash(const std::vector<int>& base, const int c)
{
	long result = 0, power = 1;
	for (int i = 0; i < base.size(); i++)
	{
		result += base[base.size() - 1 - i] * power;
		power *= c;
	}
	return result;
};

inline void ComputeTranslationIndexesForN(const int n, std::vector<int>& indexes)
{
	const int r0 = n - 1;

	int i = 0;
	int current_index = 0;
	for (int q = -r0; q <= r0 - 1; q++) {
		int count = 0;
		const int r1 = std::max(-r0, -q - r0);
		const int r2 = std::min(r0, -q + r0);
		for (int r = r1; r <= r2; r++) {
			if (q >= 0 && count + q >= n * 2 - 2)
			{
				++i;
				continue;
			}
			indexes[current_index] = i;
			++i;
			++current_index;
			++count;
		}
	}
}

inline bool Agrees(
	std::vector<int>& p1,
	std::vector<int>& p2,
	std::vector<int>& Indexes,
	std::vector<int>& RotatedIndexes,
	std::vector<int>& TranslatedIndexes
	)
{
	for (const int index: Indexes)
	{
		if (p1[RotatedIndexes[index]] != p2[TranslatedIndexes[index]]) return false;
	}

	return true;
}