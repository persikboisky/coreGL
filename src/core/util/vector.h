#pragma once

#include <vector>

namespace vector 
{
	int searchElemntForValue(std::vector<int> vec, int value);
	int searchElemntForValue(std::vector<unsigned int> vec, int value);

	std::vector<float> arrayToVector(float* array, unsigned int size_array);
	//std::vector<int> IarrayToIVector(int* array, int size_array);
}