#define PATH_TO_VERTEX_SHADER "./res/shaders/GUI/vert.glsl"
#define PATH_TO_FRAGMENT_SHADER "./res/shaders/GUI/frag.glsl"
#define DEBUG true

#include "GUI.hpp"
#include "../vao.hpp"
#include "../shader.hpp"
#include <GL/glew.h>
#include <vector>
#include <iostream>

enum primitive
{
	TRIANGLE_STRIP = GL_TRIANGLES,
};

GUI::Body::Body()
{

}

GUI::Body::~Body()
{

}

void GUI::Body::startCreate()
{

}

//void GUI::Body::addColor(float red, float green, float blue, float alhpa = 1)
//{
//	this->currentIndexSettings++;
//}

void GUI::Body::createButton(float x, float y, float width, float height, int id = 0)
{
	this->id.push_back(id);

	std::vector<float> vert;

	//вершина 1
	vert.push_back(x);
	vert.push_back(y);
	//вершина 2
	vert.push_back(x);
	vert.push_back(y - height);
	//вершина 3
	vert.push_back(x + width);
	vert.push_back(y - height);

	//вершина 4
	vert.push_back(x);
	vert.push_back(y);
	//вершина 5
	vert.push_back(x + width);
	vert.push_back(y);
	//вершина 6
	vert.push_back(x + width);
	vert.push_back(y - height);

	this->vertex.push_back(vert);
	vert.clear();

	if (DEBUG)
	{
		std::cout << "OK: create button to index = " << this->currentIndexElement << ", id = " << id << std::endl;
	}
	this->currentIndexElement++;
}

void GUI::Body::endCreate()
{
	this->shader = new Shader(PATH_TO_VERTEX_SHADER, PATH_TO_FRAGMENT_SHADER);

	std::vector<float> Vao;

	for (unsigned int i = 0; i < this->vertex.size(); i++)
	{
		for (unsigned int j = 0; j < this->vertex[0].size(); j++)
		{
			Vao.push_back(this->vertex[i][j]);
			std::cout << this->vertex[i][j] << std::endl;
		}
	}

	this->vao = new VAO(Vao, 2);
	this->vao->addAttribute(0, 2, 0);
	Vao.clear();
}

void GUI::Body::Render()
{
	this->shader->use();
	this->vao->draw(TRIANGLE_STRIP);
}