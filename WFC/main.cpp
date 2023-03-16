#include <iostream>
#include <vector>

#include "src/Models/OverlappingModel.h"
#include "src/Models/Utils/PerformanceMeasurement.h"
#include "src/Models/Utils/PrintColor.h"

int main()
{
	std::vector<int> bitmap = {
		1, 1, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 5, 1, 1, 5, 1, 1, 5, 1, 1, 1, 2, 2, 1, 1, 1, 5, 1, 1, 1, 0, 0, 0, 0, 5, 5, 5,
		 1, 1, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 2, 2, 1, 5, 1, 1, 1, 1, 5, 5, 0, 0, 0, 5, 5, 5, 5,
		1, 1, 5, 5, 5, 2, 5, 5, 5, 5, 2, 2, 2, 1, 0, 0, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 5, 5, 1, 1, 1, 5, 0, 1, 1, 1, 0, 5, 5, 5,
		 1, 1, 5, 5, 2, 5, 5, 5, 5, 5, 2, 5, 5, 0, 0, 1, 1, 2, 2, 2, 0, 0, 5, 5, 0, 1, 5, 5, 1, 1, 5, 5, 1, 1, 1, 5, 0, 0, 1, 1, 1, 5, 1, 1, 1, 1, 0, 2, 2, 2, 2, 0, 5, 5, 5,
		0, 0, 0, 0, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 1, 1, 2, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 2, 1, 5, 0, 0, 2, 3, 3, 3, 2, 0, 1, 1,
		 0, 0, 0, 0, 1, 1, 1, 2, 2, 5, 5, 5, 5, 0, 0, 1, 1, 2, 2, 5, 0, 3, 3, 3, 0, 0, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 0, 0, 5, 5, 2, 2, 2, 1, 5, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 2, 0, 0, 3, 3, 3, 3, 0, 5, 5, 5, 1, 1, 1, 2, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 3, 2, 1, 0,
		 0, 0, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 2, 0, 0, 3, 3, 3, 3, 3, 0, 5, 5, 1, 1, 5, 2, 2, 2, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0,
		0, 0, 0, 0, 0, 5, 2, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 2, 5, 5, 0, 3, 3, 3, 3, 0, 5, 5, 5, 1, 1, 1, 1, 1, 1, 2, 0, 0, 5, 5, 1, 1, 5, 1, 1, 5, 0, 2, 3, 3, 3, 2, 0, 5, 1,
		 2, 2, 2, 2, 5, 2, 2, 2, 2, 5, 5, 0, 5, 5, 1, 2, 2, 1, 5, 0, 0, 3, 3, 3, 0, 5, 5, 5, 1, 1, 1, 1, 0, 5, 2, 2, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 0, 1, 1, 1,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 6, 5, 5, 5, 5, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 0, 1, 1, 1,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 5, 5, 5, 1, 1, 5, 5, 1, 0, 0, 0, 0, 1, 1, 1, 1, 5, 1, 1, 1, 1, 5, 5, 0, 0, 5, 1, 1, 5, 5,
		0, 0, 0, 5, 5, 0, 0, 3, 3, 3, 5, 5, 5, 5, 5, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 5, 1, 1, 1, 5, 0, 0, 5, 1, 1, 5, 1, 1, 5, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
		 1, 1, 1, 0, 0, 0, 0, 3, 3, 3, 5, 5, 5, 5, 2, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 1, 1, 1, 5, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
		1, 5, 1, 1, 0, 0, 0, 3, 3, 3, 0, 0, 1, 2, 2, 2, 5, 1, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 0, 0, 5, 0, 2, 2, 2,
		 1, 5, 1, 1, 5, 5, 5, 5, 5, 0, 3, 3, 1, 2, 2, 2, 5, 2, 2, 5, 5, 5, 2, 2, 2, 5, 5, 5, 3, 3, 3, 1, 5, 1, 0, 0, 5, 1, 1, 1, 1, 5, 1, 1, 1, 5, 5, 0, 0, 5, 0, 2, 5, 5, 2,
		1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 3, 3, 3, 1, 2, 2, 2, 2, 2, 2, 5, 5, 5, 2, 2, 2, 5, 5, 5, 1, 5, 1, 1, 1, 0, 0, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 2, 5, 2,
		 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 3, 3, 1, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 2, 2, 5, 5, 5, 5, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 2, 2, 2, 2,
		0, 0, 1, 1, 1, 2, 2, 2, 5, 5, 5, 5, 1, 2, 5, 5, 5, 2, 2, 2, 1, 5, 5, 2, 2, 2, 5, 5, 5, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 0, 2, 2, 2, 2,
		 0, 0, 1, 1, 1, 2, 2, 2, 5, 5, 5, 2, 2, 2, 5, 5, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 2, 1, 1, 2, 0, 5, 5, 1, 1, 1, 1, 1, 1, 5, 5, 1, 0, 2, 2, 5, 5, 5,
		5, 5, 5, 1, 0, 0, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 5, 5, 0, 0, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 0, 2, 2, 5, 5, 5,
		 5, 5, 5, 0, 0, 2, 5, 5, 1, 1, 2, 2, 5, 1, 1, 1, 1, 5, 5, 1, 2, 2, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 2, 2, 3, 3, 2, 2, 0, 1, 1, 1, 5, 2, 2, 1, 1, 1, 0, 2, 2, 2, 5, 5, 5,
		5, 5, 5, 5, 0, 0, 2, 5, 1, 1, 2, 2, 1, 1, 1, 1, 5, 5, 5, 5, 2, 2, 2, 2, 5, 5, 1, 0, 0, 0, 0, 0, 2, 2, 3, 3, 3, 2, 2, 0, 5, 1, 1, 2, 2, 2, 1, 5, 0, 2, 2, 2, 5, 5, 5,
		 5, 5, 5, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 5, 5, 5, 5, 2, 2, 2, 2, 2, 5, 5, 0, 0, 1, 1, 1, 0, 2, 2, 3, 3, 2, 2, 0, 5, 1, 1, 1, 2, 1, 1, 0, 0, 2, 2, 2, 5, 5, 5, 1,
		5, 5, 5, 2, 2, 2, 2, 2, 2, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 1, 1, 2, 2, 5, 0, 0, 1, 5, 5, 5, 0, 2, 2, 2, 2, 2, 0, 1, 1, 1, 5, 5, 1, 1, 1, 0, 2, 2, 2, 2, 5, 5, 1,
		 5, 5, 5, 2, 0, 0, 2, 2, 2, 6, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 1, 1, 2, 2, 2, 0, 0, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1,
		5, 5, 5, 2, 0, 5, 0, 1, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1,
		 5, 5, 5, 1, 5, 5, 5, 1, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 5, 5, 5, 1, 1, 2, 5, 2, 2, 5, 2, 0, 0, 0, 5, 5,
		5, 5, 5, 2, 1, 0, 5, 1, 1, 1, 2, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 0, 0, 1, 5, 5, 5, 5, 3, 3, 3, 3, 3, 5, 5, 1, 1, 0, 5, 5, 2, 2, 5, 0, 0, 0, 5, 5,
		 5, 5, 5, 2, 2, 0, 1, 0, 0, 1, 2, 1, 2, 2, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 5, 5,
		5, 5, 5, 2, 2, 2, 1, 0, 5, 5, 1, 2, 1, 2, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 5, 0, 0, 2, 1, 2, 2, 2, 2, 2, 5, 5,
		 5, 5, 5, 2, 2, 2, 1, 0, 0, 1, 2, 2, 2, 2, 1, 6, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 0, 0, 1, 1, 5, 5, 1, 1, 1, 5, 5, 2, 2, 2, 2, 2, 5, 5, 0, 1, 2, 0, 0, 5, 5, 2, 5, 5,
		5, 5, 5, 2, 2, 2, 2, 2, 1, 1, 2, 0, 1, 2, 1, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 0, 0, 1, 5, 5, 1, 1, 1, 2, 5, 2, 2, 2, 2, 1, 1, 1, 0, 1, 5, 0, 3, 3, 3, 5, 2, 1,
		 5, 5, 5, 0, 0, 1, 1, 2, 2, 2, 0, 5, 1, 2, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 5, 2, 1, 1, 0, 1, 5, 5, 3, 3, 3, 3, 0, 2, 1,
		5, 5, 5, 6, 3, 3, 3, 1, 2, 2, 1, 5, 5, 1, 5, 5, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 1, 1, 5, 5, 2, 2, 0, 0, 2, 2, 1, 1, 5, 1, 2, 5, 3, 3, 3, 3, 3, 0, 2,
		 5, 5, 5, 3, 3, 3, 3, 0, 2, 2, 1, 1, 1, 2, 5, 5, 5, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 1, 1, 5, 5, 5, 2, 2, 2, 0, 1, 1, 1, 0, 0, 1, 2, 0, 3, 3, 3, 3, 0, 2, 1,
		5, 5, 5, 3, 3, 3, 3, 3, 0, 2, 2, 2, 2, 2, 5, 5, 5, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 1, 1, 5, 5, 1, 0, 5, 5, 1, 1, 5, 1, 0, 0, 1, 2, 0, 3, 3, 3, 0, 5, 5,
		 5, 5, 5, 3, 3, 3, 3, 5, 5, 2, 5, 2, 2, 3, 3, 3, 1, 1, 1, 5, 5, 2, 2, 2, 3, 3, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 0, 0, 5, 5, 1, 1, 5, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 5,
		5, 5, 5, 5, 3, 3, 3, 5, 5, 5, 2, 5, 2, 3, 3, 3, 1, 1, 1, 5, 5, 5, 2, 2, 3, 3, 3, 5, 5, 5, 5, 5, 2, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 5, 2, 2, 2, 2, 5, 5, 5,
		 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2, 3, 3, 3, 1, 1, 1, 5, 5, 2, 2, 2, 3, 3, 5, 5, 5, 5, 5, 2, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 5, 5, 5 };
	

	/*
	std::vector<int> bitmap = {
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
	 };
	 */


	// Flower
	/*
	int W = 15;
	int H = 24;
	std::vector<int> bitmap = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,
		 0,0,0,0,1,2,1,0,0,0,0,0,1,2,1,
		0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,
		0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,
		 1,1,0,0,0,0,2,2,0,0,0,0,2,0,0,
		1,2,1,0,0,0,0,2,0,0,0,0,2,0,0,
		 1,1,0,0,0,0,2,0,0,0,0,2,2,0,0,
		0,2,0,0,0,0,2,0,0,1,1,0,2,2,0,
		 0,2,0,0,0,2,2,0,1,2,1,0,0,2,0,
		0,0,2,0,0,2,0,0,0,1,1,0,0,2,0,
		 0,0,2,2,2,0,0,0,0,2,0,0,2,0,0,
		0,0,0,2,0,0,0,0,0,2,0,2,2,0,0,
		 0,0,0,2,2,0,0,0,0,2,2,2,0,0,0,
		0,0,0,0,2,2,0,0,0,0,2,0,0,0,0,
		 0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,
		0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,
		 0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,
		0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,
		3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,
		 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	};
	*/

	// Damier
	/**/
	int W = 9;
	int H = 9;
	std::vector<int> bitmap2 = {
		1,1,1,1,1,1,1,1,1,
		 1,2,1,2,1,2,1,2,1,
		1,1,1,1,1,1,1,1,1,
		 1,2,1,2,1,2,1,2,1,
		1,1,1,1,1,1,1,1,1,
		 1,2,1,2,1,2,1,2,1,
		1,1,1,1,1,1,1,1,1,
		 1,2,1,2,1,2,1,2,1,
		1,1,1,1,1,1,1,1,1
	};

	std::vector<int> bitmap3 = {
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1
	};


	std::vector<int> bitmap4 = {
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1,
	 1,2,1,2,1,2,1,2,1,
	1,2,1,2,1,2,1,2,1
	};

	std::vector<int> bitmap5 = {
		0,0,0,0,0,0,0,0,0,0,
		 0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,2,3,5,1,0,
		 1,3,2,1,1,2,3,5,1,0,
		1,5,3,2,1,1,2,3,5,1,
		 1,5,3,2,1,2,3,5,1,0,
		0,1,5,3,2,2,3,5,1,0,
		 0,1,5,3,3,3,5,1,0,0,
		0,0,1,5,5,5,5,1,0,0,
		 0,0,1,1,1,1,1,0,0,0
	};

	
	
	PerformanceMeasurement p;

	std::vector<std::vector<int>> maps;
	maps.push_back(bitmap5);

	const std::vector<MapSize> model_sizes = { {10,10} };

	const int symmetry = 1;
	const int N = 2;

	const MapSize output_size = { 30, 30 };

	OverlappingModel model = OverlappingModel(maps, model_sizes, symmetry, N, output_size);

	std::vector<int> output_datas;
	bool done = false;

	for (int k = 0; k < 100; k++)
	{
		if (model.Run(-1))
		{
			output_datas.clear();
			done = model.Save(output_datas);
			if (done) break;
		}
		std::cout << "CONTRADICTION" << std::endl;
	}

	if (done) {
		for (int i = output_size.height - 1; i >= 0; --i)
		{
			if (i % 2 == 0) std::cout << " ";
			for (int j = output_size.width - 1; j >= 0; --j)
			{
				switch (output_datas[i * output_size.width + j])
				{
				case 0:
					print_white(output_datas[i * output_size.width + j]);
					break;
				case 1:
					print_blue(output_datas[i * output_size.width + j]);
					break;
				case 2:
					print_red(output_datas[i * output_size.width + j]);
					break;
				case 3:
					print_green(output_datas[i * output_size.width + j]);
					break;
				case 5:
					print_pink(output_datas[i * output_size.width + j]);
					break;
				case 6:
					print_other(output_datas[i * output_size.width + j]);
					break;
				}
			}
			std::cout << '\n';
		}
	}
}

