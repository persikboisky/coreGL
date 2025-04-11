#pragma once

#include <vector>

struct ebo
{
private:
	static std::vector<unsigned int> id;

public:
	static void bind(unsigned int id);

	static unsigned int create(unsigned int* indices, unsigned int sizeOfByte);
	static unsigned int create(std::vector<unsigned int> indices);

	static void Delete(unsigned int id);
	static void DeleteALL();
};
