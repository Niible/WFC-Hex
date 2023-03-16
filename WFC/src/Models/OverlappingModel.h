#pragma once
#include "Model.h"

class OverlappingModel: public Model
{
public:
	OverlappingModel(
		const std::vector<std::vector<int>>& input_model_datas,
		const std::vector<MapSize>& input_model_sizes,
		const int symmetry,
		const int ns,
		const MapSize& output_map_size
	);


	bool Save(std::vector<int>& output_datas) override;

private:
	std::vector<std::vector<int>> patterns;

	/*
	 * This vector store colors (or representation of colors)
	 * as an index. 
	 */
	std::vector<int> colors;
};

