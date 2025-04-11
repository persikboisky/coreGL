#include "fbo.hpp"
#include "../../util/vector.hpp"
#include <GL/glew.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> fbo::id;

unsigned int fbo::create()
{
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);

	if (FBO <= 0)
	{
		std::cerr << "Failed: create FBO" << std::endl;
		throw "FAILED_CREATE_FBO";
	}

	fbo::id.push_back(FBO);
}

void fbo::Delete(unsigned int id)
{
	int index = vector::searchElemntForValue(fbo::id, id);
	if (index == -1)
	{
		std::cerr << "FAILED: delete FBO" << std::endl;
		throw "FAILED_DELETE_FBO";
	}

	glDeleteFramebuffers(1, &fbo::id[index]);

	std::vector<unsigned int>::const_iterator iterID = fbo::id.cbegin();
	fbo::id.erase(iterID + index);
}

void fbo::DeleteALL()
{
	for (unsigned int index = 0; index < fbo::id.size(); index++)
	{
		glDeleteFramebuffers(1, &fbo::id[index]);
	}

	fbo::id.clear();
}