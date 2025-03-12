#define PATH_TO_VERTEX_SHADER "./res/shaders/GUI/vert.glsl"
#define PATH_TO_FRAGMENT_SHADER "./res/shaders/GUI/frag.glsl"
#define DEBUG true

#include "GUI.hpp"
#include "Style.hpp"
#include "../vao.hpp"
#include "../shader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

// параметры по умолчанию
const glm::vec4 BACKGROUNE = glm::vec4(1, 1, 1, 1);
const glm::vec4 COLOR = glm::vec4(0.1, 0.1, 0.1, 1);
const std::string TEXT = "";

enum primitive
{
	TRIANGLE_STRIP = GL_TRIANGLES
};

void GUI::Body::addElement(int x, int y, float width, float height, GUI::Style* style)
{
	this->id.push_back(this->SelectID);
	this->cord_and_size.push_back(glm::vec4(x, y, width, height));
	this->style.push_back(style);
	this->SelectID++;
}

GUI::Body::Body()
{

}

GUI::Body::~Body()
{

}

void GUI::Body::addButton(int x, int y, float width, float height, void* function, GUI::Style* style)
{
	if (style == nullptr)
	{
		style = new Style();
		style->background = BACKGROUNE;
		style->color = COLOR;
		style->text = TEXT;
		style->flag = true;
	}
	else
	{

	}
	//std::cout << style->background.x << std::endl;
	this->addElement(x, y, width, height, style);
}

void GUI::Body::compile()
{
	//x, y, u, v, 
	std::vector<float> vao;

	for (unsigned int ID = 0; ID < this->id.size(); ID++)
	{

	}
}

void GUI::Body::render()
{
	//if event 
	//{
	//	This->compile();
	//}
	//draw {
	//	
	//}
}