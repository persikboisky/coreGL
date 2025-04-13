#include "fbo.hpp"
#include "../../util/vector.hpp"
#include <GL/glew.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> fbo::id;
unsigned int fbo::selectID = 0;

void fbo::bind(unsigned int id)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	fbo::selectID = id;
}

void fbo::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	fbo::selectID = 0;
}

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
	return FBO;
}

void fbo::linkTexture(unsigned int t_id)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, t_id, 0);
}

void fbo::Delete(unsigned int id)
{
	unsigned int index = vector::searchElemntForValue(fbo::id, id);

	if (index != -1)
	{
		glDeleteFramebuffers(1, &fbo::id[index]);
		std::vector<unsigned int>::const_iterator iterID = fbo::id.cbegin();
		fbo::id.erase(iterID + index);
	}
}

void fbo::DeleteALL()
{
	for (unsigned int index = 0; index < fbo::id.size(); index++)
	{
		glDeleteFramebuffers(1, &fbo::id[index]);
	}

	fbo::id.clear();
}