#include "rbo.hpp"
#include "../../util/vector.hpp"
#include <GL/glew.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> rbo::id;
unsigned int rbo::SelectID = 0;

void rbo::bind(unsigned int id)
{
	glBindRenderbuffer(GL_RENDERBUFFER, id);
	rbo::SelectID = id;
}

unsigned int rbo::create()
{
	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);

	if (RBO <= 0)
	{
		std::cerr << "Failed: create RBO" << std::endl;
		throw "FAILED_CREATE_RBO";
	}

	rbo::id.push_back(RBO);
	return RBO;
}

void rbo::Delete(unsigned int id)
{
	unsigned int index = vector::searchElemntForValue(rbo::id, id);

	if (index != -1)
	{
		glDeleteRenderbuffers(1, &rbo::id[index]);
		std::vector<unsigned int>::const_iterator iterID = rbo::id.cbegin();
		rbo::id.erase(iterID + id);
	}
}

void rbo::DeleteALL()
{
	for (unsigned int index = 0; index < rbo::id.size(); index++)
	{
		glDeleteRenderbuffers(1, &rbo::id[index]);
		rbo::id.clear();
	}
}