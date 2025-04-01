#include "GUI.hpp"
#include "gui_style.hpp"
#include "../commons/vao.hpp"
#include "../commons/font.hpp"
#include "../commons/shader.hpp"
#include "../commons/BufferText2D.hpp"
#include "../../window/Window.hpp"
#include "../../data/structs.hpp"
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <vector>
#include <iostream>

// путь к шейдерам для отрисовки gui контента
constexpr const char* PATH_TO_VERTEX_SHADER = "./res/gui/main_gui_v.glsl";
constexpr const char* PATH_TO_FRAGMENT_SHADER = "./res/gui/main_gui_f.glsl";

enum primitive
{
	TRIANGLE = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP
};

GUI::GUI(Window* window) : n_Elements(0), vao(nullptr), window(window)
{
	this->shader = new Shader(PATH_TO_VERTEX_SHADER, PATH_TO_FRAGMENT_SHADER);
	this->TextFont = new font();
	this->BT2D = new BufferText2D();
	this->BT2D->linkFont(this->TextFont);
}

GUI::~GUI()
{
	delete this->shader;
	delete this->vao;
	delete this->TextFont;
	delete this->BT2D;
	this->style.clear();
}

static void addVertexesToVector(std::vector<float>& vec, glm::vec4& data)
{
	vec.push_back(data.x);
	vec.push_back(data.y);

	vec.push_back(data.x);
	vec.push_back(data.y - data.w);

	vec.push_back(data.x + data.z);
	vec.push_back(data.y - data.w);

	vec.push_back(data.x);
	vec.push_back(data.y);

	vec.push_back(data.x + data.z);
	vec.push_back(data.y - data.w);

	vec.push_back(data.x + data.z);
	vec.push_back(data.y);
}

void GUI::compileVAO()
{
	this->compileFlag = false;

	std::vector<float> vao;

	for (unsigned int index = 0; index < this->n_Elements; index++)
	{
		glm::vec4 elementData = glm::vec4(
			this->style[index].x, this->style[index].y,
			this->style[index].width, this->style[index].height
		);
		addVertexesToVector(vao, elementData);

		if (this->style[index].text != "")
		{
			// доделать !!!
			this->BT2D->addText(
				this->style[index].text,
				0,
				0,
				0.3f
			);
		}
	}

	this->vao = new VAO(vao, 2);
	this->vao->addAttribute(0, 2, 0);
}

void GUI::addButton(
	gui_style* style,
	void(*function)()
)
{
	this->style.push_back(*style);
	this->elements.push_back(BUTTON);
	this->function.push_back(function);

	n_Elements++;
}

void GUI::setWindow(Window* window)
{
	this->window = window;
}

bool flag = false;
void GUI::render()
{
	if (this->compileFlag)
	{
		if (flag)
			this->BT2D->DeleteText();
		else 
			flag = true;

		this->compileVAO();
	}

	this->BT2D->render();

	this->shader->use();
	for (unsigned int index = 0; index < this->n_Elements; index++)
	{
		double MouseX, MouseY;

		this->window->cursor->getCordCursor(MouseX, MouseY);

		MouseX = MouseX / double(window->width / 2.0) - 1.0;
		MouseY = -(MouseY / double(window->height / 2.0) - 1.0);

		glm::vec4 background = glm::vec4(
			this->style[index].background.red / 255.0f,
			this->style[index].background.green / 255.0f,
			this->style[index].background.blue / 255.0f,
			this->style[index].background.alpha / 255.0f
		);

		switch (this->elements[index])
		{
		case BUTTON:
			if (
				MouseX >= double(this->style[index].x) &&
				MouseX <= double(this->style[index].x + this->style[index].width) &&
				MouseY <= this->style[index].y &&
				MouseY >= this->style[index].y - this->style[index].height &&
				this->window->event->GetMouseLeftButton()
			)
			{
				background = glm::vec4(
					this->style[index].active_background.red / 255.0f,
					this->style[index].active_background.green / 255.0f,
					this->style[index].active_background.blue / 255.0f,
					this->style[index].active_background.alpha / 255.0f
				);

				if (this->function[index] != nullptr)
				{
					this->function[index]();
				}
			}
			break;
		}

		this->shader->Uniform4F(glm::vec4(background), "background");
		this->vao->draw(TRIANGLE, index * 6, index * 6 + 6);
	}
}