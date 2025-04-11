#include "ebo.hpp"
#include "../../util/vector.hpp"
#include <GL/glew.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> ebo::id;

void ebo::bind(unsigned int id)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

unsigned int ebo::create(unsigned int* indices, unsigned int sizeOfByte)
{
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	
	if (EBO <= 0)
	{
		std::cerr << "Failed create VAO" << "\n";
		throw "FAILED_CREATE_VAO";
	}

	ebo::bind(EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfByte, indices, GL_STATIC_DRAW);
	ebo::bind(0);

	ebo::id.push_back(EBO);
	return EBO;
}

unsigned int ebo::create(std::vector<unsigned int> indices)
{
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	if (EBO <= 0)
	{
		std::cerr << "Failed create VAO" << "\n";
		throw "FAILED_CREATE_VAO";
	}

	ebo::bind(EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
	ebo::bind(0);

	ebo::id.push_back(EBO);
	return EBO;
}

void ebo::Delete(unsigned int id)
{
	int index = vector::searchElemntForValue(ebo::id, id);

	if (index != -1)
	{
		glDeleteBuffers(1, &ebo::id[index]);
		std::vector<unsigned int>::const_iterator Iter = ebo::id.cbegin();
		ebo::id.erase(Iter + index);
	}
}

void ebo::DeleteALL()
{
	for (unsigned int index = 0; index < ebo::id.size(); index++)
	{
		glDeleteBuffers(1, &ebo::id[index]);
	}
}