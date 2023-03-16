#pragma once
#include <array>
#include <utility>

struct OddrCoordinates
{
	int x;
	int y;
	bool operator==(const OddrCoordinates& coordinates) const
	{
		return x == coordinates.x && y == coordinates.y;
	}
};

struct CubeHexCoordinates
{
	int q;
	int r;
	int GetS() const { return  -q - r; }

	bool operator==(const CubeHexCoordinates& coordinates) const
	{
		return q == coordinates.q && r == coordinates.r;
	}
};

inline int GetRowOffset(const int row_index)
{
	// flip flop (i % 2) the rowOffset to construct the grid
	// bitwise works with negative numbers
	return row_index & 1;
}

inline int GetIndexForOddrCoordinates(const OddrCoordinates& coordinates, const int& grid_width, const int& grid_height)
{
	if (coordinates.x < 0 || coordinates.x >= grid_width || coordinates.y < 0 || coordinates.y >= grid_height) return -1;
	return coordinates.y * grid_width + coordinates.x;
}

inline OddrCoordinates GetGridCoordinatesForIndex(const int index, const int grid_width)
{
	const auto x = index % grid_width;
	return { x, (index - x) / grid_width };
}


inline CubeHexCoordinates GetCubeCoordinatesFromOddr(const OddrCoordinates coordinates)
{
	return {
		coordinates.x - (coordinates.y - GetRowOffset(coordinates.y)) / 2,
		coordinates.y,
	};
}

inline OddrCoordinates GetOddrCoordinatesFromCube(const CubeHexCoordinates coordinates)
{
	return {
		coordinates.q + (coordinates.r - GetRowOffset(coordinates.r)) / 2,
		coordinates.r,
	};
}

inline void GetCubeNeighbors(const CubeHexCoordinates coordinates, std::array<CubeHexCoordinates, 6>& neighbors)
{
	neighbors[0] = { coordinates.q + 1, coordinates.r };
	neighbors[1] = { coordinates.q + 1, coordinates.r - 1 };
	neighbors[2] = { coordinates.q, coordinates.r - 1};
	neighbors[3] = { coordinates.q - 1, coordinates.r };
	neighbors[4] = { coordinates.q - 1, coordinates.r + 1 };
	neighbors[5] = { coordinates.q, coordinates.r + 1};
}

inline void RotateCubeClockwise(const CubeHexCoordinates hex, const CubeHexCoordinates center, CubeHexCoordinates& rotated_hex) {
	//Calculate a vector by subtracting the center: 
	//const auto vec = CubeHexCoordinates(hex.q - center.q, hex.r - center.r);
	/*
		[ q,  r,  s]
	to  [-r, -s, -q]
	to  [  s,  q,  r]
	*/
	//const auto rotated_vec = CubeHexCoordinates(-vec.r, -vec.GetS());
	//return { rotated_vec.q + center.q, rotated_vec.r + center.r };
	const auto q = hex.q - center.q;
	const auto r = hex.r - center.r;
	const auto s = -q - r;

	rotated_hex.q = -r + center.q;
	rotated_hex.r = -s + center.r;
}

template<int count>
inline void RotateCubeClockwise(CubeHexCoordinates& hex)
{
}

template<>
inline void RotateCubeClockwise<1>(CubeHexCoordinates& hex)
{
	const auto r = hex.r;
	const auto s = hex.GetS();
	hex.q = -r;
	hex.r = -s;
}

template<>
inline void RotateCubeClockwise<2>(CubeHexCoordinates& hex)
{
	const auto q = hex.q;
	const auto s = hex.GetS();
	hex.q = s;
	hex.r = q;
}

template<>
inline void RotateCubeClockwise<3>(CubeHexCoordinates& hex)
{
	hex.q = -hex.q;
	hex.r = -hex.r;
}

template<>
inline void RotateCubeClockwise<4>(CubeHexCoordinates& hex)
{
	const auto r = hex.r;
	const auto s = hex.GetS();

	hex.q = r;
	hex.r = s;
}

template<>
inline void RotateCubeClockwise<5>(CubeHexCoordinates& hex)
{
	const auto q = hex.q;
	const auto s = hex.GetS();

	hex.q = -s;
	hex.r = -q;
}

inline void RotateCubeClockwise(CubeHexCoordinates& hex, int count)
{
	switch (count)
	{
	case 1:
		return RotateCubeClockwise<1>(hex);
	case 2:
		return RotateCubeClockwise<2>(hex);
	case 3:
		return RotateCubeClockwise<3>(hex);
	case 4:
		return RotateCubeClockwise<4>(hex);
	case 5:
		return RotateCubeClockwise<5>(hex);
	}
}

/*
inline void RotateCubeClockwise(CubeHexCoordinates& hex, const CubeHexCoordinates center) {
	//Calculate a vector by subtracting the center: 
	//const auto vec = CubeHexCoordinates(hex.q - center.q, hex.r - center.r);
	//	[ q,  r,  s]
	//  to  [-r, -s, -q]
	//    to  [  s,  q,  r]
	//const auto rotated_vec = CubeHexCoordinates(-vec.r, -vec.GetS());
	//return { rotated_vec.q + center.q, rotated_vec.r + center.r };
	const auto q = hex.q - center.q;
	const auto r = hex.r - center.r;
	const auto s = -q - r;

	hex.q = -r + center.q;
	hex.r = -s + center.r;
}
*/

// self included
inline void GetNeighborsCubeCoordinatesInRadius(const CubeHexCoordinates& coordinates, const int radius, std::vector<CubeHexCoordinates>& neighbors)
{
	int i = 0;
	const int r0 = radius - 1;

	for (int q = -r0; q <= r0; q++) {
		const int r1 = std::max(-r0, -q - r0);
		const int r2 = std::min(r0, -q + r0);
		for (int r = r1; r <= r2; r++) {
			//if (q == 0 && r == 0) continue;
			neighbors[i] = { coordinates.q + q, coordinates.r + r };
			++i;
		}
	}
}

// self included
template<size_t Size>
inline void GetNeighborsCubeCoordinatesInRadius(const CubeHexCoordinates coordinates, const int radius, std::array<CubeHexCoordinates, Size>& neighbors, std::array<CubeHexCoordinates, Size>& rotated_neighbors)
{
	int i = 0;
	const int r0 = radius - 1;

	for (int q = -r0; q <= r0; q++) {
		const int r1 = std::max(-r0, -q - r0);
		const int r2 = std::min(r0, -q + r0);
		for (int r = r1; r <= r2; r++) {
			//if (q == 0 && r == 0) continue;
			neighbors[i] = { coordinates.q + q, coordinates.r + r };
			rotated_neighbors[i] = { coordinates.q + q, coordinates.r + r };
			++i;
		}
	}
}


inline CubeHexCoordinates ReflectSCube(const CubeHexCoordinates hex, const CubeHexCoordinates center) {
	//Calculate a vector by subtracting the center: 
	const auto vec = CubeHexCoordinates(hex.q - center.q, hex.r - center.r);
	const auto reflected_vec = CubeHexCoordinates(vec.r, vec.q);

	return { reflected_vec.q + center.q, reflected_vec.r + center.r };
}
