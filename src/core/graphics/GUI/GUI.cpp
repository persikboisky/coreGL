#define PATH_TO_VERTEX_SHADER "./res/shaders/GUI/vert.glsl"
#define PATH_TO_FRAGMENT_SHADER "./res/shaders/GUI/frag.glsl"
#define DEBUG true

#include "GUI.hpp"
#include "Style.hpp"
#include "../commons/vao.hpp"
#include "../commons/shader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

// параметры по умолчанию
const glm::vec4 S_BACKGROUNE = glm::vec4(1, 1, 1, 1);
const glm::vec4 S_COLOR = glm::vec4(0.1, 0.1, 0.1, 1);
const std::string S_TEXT = "";

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
		style->background = S_BACKGROUNE;
		style->color = S_COLOR;
		style->text = S_TEXT;
		style->flag = true;
	}
	else
	{

	}
	style->index_element = BUTTON;
	//std::cout << style->background.x << std::endl;
	this->addElement(x, y, width, height, style);
}

void GUI::Body::compile()
{
	//x, y, u, v, 
	if (this->vao != nullptr)
	{
		this->vao->~VAO();
	}

	std::vector<float> vao;

	for (unsigned int ID = 0; ID < this->style.size(); ID++)
	{
		switch (this->style[ID]->index_element)
		{
		case NONE:
			//code
			break;
		case BUTTON:
			//code
			break;
		case TEXT:
			//code
			break;
		case SLIDER:
			//code
			break;
		case IMAGE:
			//code
			break;
		default:
			break;
		}
	}

	//this->vao = new VAO();
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