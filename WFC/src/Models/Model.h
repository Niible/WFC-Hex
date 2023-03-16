#pragma once

#include <array>
#include <vector>
#include <utility>

#include "Config.h"
#include "Utils/MapSize.h"


struct CellInfo
{
	std::vector<bool> wave;
	std::array<std::vector<int>, NumberOfNeighbors> compatible;
	std::vector<std::vector<int>> propagator;

	// D : number of nei : 6
	// T : Number of patterns
	// l : id pattern compatible

	int observed;
	int sumsOfOnes;
	double entropies;
	double sumOfWeights;
	double sumOfWeightLogWeights;

	CellInfo() {}

	void Init(const int T)
	{
		Reset(T);
		//propagator = std::vector<std::vector<int>>(NumberOfNeighbors);
		entropies = 0;
		sumOfWeights = 0;
		sumOfWeightLogWeights = 0;
		for (int i = 0; i < NumberOfNeighbors; ++i)
		{
			compatible[i] = std::vector<int>(T);
		}
	}

	void InitEntropy(const double startingEntropy, const double sumsOfWeights, const double sumsOfWeightLogWeights)
	{
		entropies = startingEntropy;
		sumOfWeights = sumsOfWeights;
		sumOfWeightLogWeights = sumsOfWeightLogWeights;
	}

	void Reset(const int T)
	{
		wave = std::vector(T, true);
		observed = -1;
		sumsOfOnes = T;
	}

};

class Model
{
public:

	Model(int n, const MapSize& output_size): n(n), output_size(output_size) {};

	virtual ~Model() = default;

	bool Run(int limit);

	virtual bool Save(std::vector<int>& output_datas) = 0;

	std::vector<CellInfo> cellInfos;

	void InitCellInfo(int t);
	void InitCellEntropies(double startingEntropy, double sumOfWeights, double sumOfWeightLogWeights);

private:

	void Init();

	int NextUnobservedNode();

	void Observe(int node);

	bool Propagate();

	void Ban(int i, int t);

	void Clear();

protected:
	std::vector<std::pair<int, int>> stack;

	std::vector<std::vector<std::vector<int>>> propagator;

	// rename outputWidth and outputHeight
	MapSize output_size;

	int T = 0;

	std::vector<double> weights;

	static std::array<int, NumberOfNeighbors> dx;
	static std::array<int, NumberOfNeighbors> dy;

	int n;

private:

	int stacksize = 0;
	int observedSoFar = 0;

	std::vector<double> weightLogWeights, distribution;

	static std::array<int, NumberOfNeighbors> opposite;
};
