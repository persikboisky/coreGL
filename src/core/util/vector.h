#pragma once

#include <vector>

namespace vector 
{
	int searchElemntForValue(std::vector<int> vec, int value);
	int searchElemntForValue(std::vector<unsigned int> vec, int value);

	std::vector<float> arrayToVector_float(float* array, unsigned int size_array);
	std::vector<int> arrayToVector_int(int* array, unsigned int size_array);
	std::vector<char> arrayToVector_char(char* array, unsigned int size_array);
}