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