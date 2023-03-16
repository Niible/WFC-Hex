#pragma once

#include <iostream>

inline void print_red(const int& message) {
	std::cout << "\033[1;31m" << message << "\033[0m ";
}

inline void print_blue(const int& message) {
	std::cout << "\033[1;34m" << message << "\033[0m ";
}

inline void print_white(const int& message) {
	std::cout << "\033[1;37m" << message << "\033[0m ";
}

inline void print_green(const int& message) {
	std::cout << "\033[1;32m" << message << "\033[0m ";
}

inline void print_pink(const int& message) {
	std::cout << "\033[1;35m" << message << "\033[0m ";
}

inline void print_other(const int& message) {
	std::cout << "\033[1;36m" << message << "\033[0m ";
}

void print_debug(std::vector<int>& map, int width, int height, bool reverse= false)
{
	if (reverse) {
		for (int i = height - 1; i >= 0; --i)
		{
			if (i % 2 == 1) std::cout << " ";
			for (int j = width - 1; j >= 0; --j)
			{
				switch (map[i * width + j])
				{
				case 0:
					print_white(map[i * width + j]);
					break;
				case 1:
					print_blue(map[i * width + j]);
					break;
				case 2:
					print_red(map[i * width + j]);
					break;
				case 3:
					print_green(map[i * width + j]);
					break;
				case 5:
					print_pink(map[i * width + j]);
					break;
				case 6:
					print_other(map[i * width + j]);
					break;
				}
			}
			std::cout << '\n';
		}
	} else
	{
		for (int i = 0 ; i < height; ++i)
		{
			if (i % 2 == 1) std::cout << " ";
			for (int j = 0; j < width; ++j)
			{
				switch (map[i * width + j])
				{
				case 0:
					print_white(map[i * width + j]);
					break;
				case 1:
					print_blue(map[i * width + j]);
					break;
				case 2:
					print_red(map[i * width + j]);
					break;
				case 3:
					print_green(map[i * width + j]);
					break;
				case 5:
					print_pink(map[i * width + j]);
					break;
				case 6:
					print_other(map[i * width + j]);
					break;
				}
			}
			std::cout << '\n';
		}
	}
}