#include "vector.h"
#include <vector>
#include <iostream>

int vector::searchElemntForValue(std::vector<int> vec, int value)
{
	int index;
	bool flag = false;

	for (int i = 0; i < vec.size(); i++)
	{

		std::cout << i;

		if (vec[i] == value)
		{
			index = i;
			flag = true;
			break;
		}
	}

	if (!flag)
	{
		return -1;
	}

	return index;
}

int vector::searchElemntForValue(std::vector<unsigned int> vec, int value)
{
	int index;
	bool flag = false;

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == value)
		{
			index = i;
			flag = true;
			break;
		}
	}

	if (!flag)
	{
		return -1;
	}

	return index;
}

std::vector<float> vector::arrayToVector(float* array, unsigned int size_array)
{
	std::vector<float> new_vector;

	for (unsigned int index = 0; index < size_array; index++)
	{
		new_vector.push_back(array[index]);
	}

	return new_vector;
}

std::vector<int> vector::IarrayToIVector(int* array, int size_array)
{
	std::vector<int> new_vector;

	for (unsigned int index = 0; index < size_array; index++)
	{
		new_vector.push_back(array[index]);
	}

	return new_vector;
}
