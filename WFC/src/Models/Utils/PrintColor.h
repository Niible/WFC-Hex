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