#pragma once
constexpr int NumberOfNeighbors = 6;
constexpr bool periodic = true;
/*
constexpr int OutputWidth = 55;
constexpr int OutputHeight = 40;
constexpr int N = 2;
constexpr int Symetry = 1;


constexpr int DataWidth = 55;
constexpr int DataHeight = 40;

constexpr int get_datas_size()
{
	return DataWidth * DataHeight;
};

constexpr int get_output_size()
{
	return OutputWidth * OutputHeight;
};

constexpr int get_hexagonal_pattern_size()
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

constexpr int get_pattern_size()
{
	return get_hexagonal_pattern_size();
};

constexpr int get_translation_array_size()
{
	constexpr int i = get_hexagonal_pattern_size();
	return i - N * 2 + 1;
};
*/