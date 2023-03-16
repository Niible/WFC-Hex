#pragma once

struct MapSize
{
	int width;
	int height;
};


inline size_t GetHexagonalPatternSize(int N)
{
	int i = 1;
	int six = 0;
	for (int k = 0; k < N - 1; ++k)
	{
		six += 6;
		i += six;
	}
	return i;
}

inline size_t GetTranslationArraySize(int N)
{
	const auto i = GetHexagonalPatternSize(N);
	return i - N * 2 + 1;
};

inline size_t GetPatternSize(int N)
{
	return GetHexagonalPatternSize(N);
};
