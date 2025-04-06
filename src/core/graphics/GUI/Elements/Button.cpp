#include "Button.hpp"
#include "../GUI_Style.hpp"
#include "../../../util/structs.hpp"
#include "../../commons/vao.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>

enum primitive
{
	TRIANGLE = GL_TRIANGLES
};

static void addVertexesButton(
	std::vector<float> &vec,
	position_4f data,
	color_rgba color
)
{
	vec.push_back(data.x);
	vec.push_back(data.y);
	vec.push_back(color.red / 255.0f);
	vec.push_back(color.green / 255.0f);
	vec.push_back(color.blue / 255.0f);
	vec.push_back(color.alpha / 255.0f);

	vec.push_back(data.x);
	vec.push_back(data.y - data.w);
	vec.push_back(color.red / 255.0f);
	vec.push_back(color.green / 255.0f);
	vec.push_back(color.blue / 255.0f);
	vec.push_back(color.alpha / 255.0f);

	vec.push_back(data.x + data.z);
	vec.push_back(data.y - data.w);
	vec.push_back(color.red / 255.0f);
	vec.push_back(color.green / 255.0f);
	vec.push_back(color.blue / 255.0f);
	vec.push_back(color.alpha / 255.0f);

	vec.push_back(data.x);
	vec.push_back(data.y);
	vec.push_back(color.red / 255.0f);
	vec.push_back(color.green / 255.0f);
	vec.push_back(color.blue / 255.0f);
	vec.push_back(color.alpha / 255.0f);

	vec.push_back(data.x + data.z);
	vec.push_back(data.y - data.w);
	vec.push_back(color.red / 255.0f);
	vec.push_back(color.green / 255.0f);
	vec.push_back(color.blue / 255.0f);
	vec.push_back(color.alpha / 255.0f);

	vec.push_back(data.x + data.z);
	vec.push_back(data.y);
	vec.push_back(color.red / 255.0f),
	vec.push_back(color.green / 255.0f);
	vec.push_back(color.blue / 255.0f);
	vec.push_back(color.alpha / 255.0f);
}

Button::Button()
{

}

Button::~Button()
{
	this->vFunction.clear();
	this->vStyle.clear();
	this->vID.clear();
	if (this->vaoID != 0)
	{
		vao::Delete(this->vaoID);
	}
}

void Button::add(
	GUIstyle style,
	void(*function)(),
	std::string ID
)
{
	bool flag = true;
	for (unsigned int index = 0; index < this->vID.size(); index++)
	{
		if (this->vID[index] == "")
		{
			this->vID[index] = ID;
			this->vStyle[index] = style;
			this->vHover[index] = false;
			this->vActive[index] = false;
			this->vFunction[index] = function;

			flag = false;
			break;
		}
	}

	if (flag)
	{
		this->vID.push_back(ID);
		this->vStyle.push_back(style);
		this->vHover.push_back(false);
		this->vActive.push_back(false);
		this->vFunction.push_back(function);
	}

	this->flagCompileVAO = true;
	this->nButton++;
}

void Button::compileVAO()
{
	if (this->vaoID != 0)
	{
		vao::Delete(this->vaoID);
	}

	std::vector<float> vertexes;

	for (unsigned int index = 0; index < this->nButton; index++)
	{
		position_4f pos = position_4f(
			this->vStyle[index].pos.x,
			this->vStyle[index].pos.y,
			this->vStyle[index].size.width,
			this->vStyle[index].size.height
		);

		color_rgba bacground;
		if (this->vActive[index])
		{
			bacground = this->vStyle[index].activeBackground;
		}
		else if (this->vStyle[index].hover && vHover[index])
		{
			bacground = this->vStyle[index].hoverBackground;
		}
		else
		{
			bacground = this->vStyle[index].background;
		}

		addVertexesButton(vertexes, pos, bacground);
	}

	this->vaoID = vao::create(vertexes);
	vao::addAttribute(this->vaoID, 0, 2, 6, 0);
	vao::addAttribute(this->vaoID, 1, 4, 6, 2);

	vertexes.clear();
}

void Button::update(double mouseX, double mouseY, bool LBM)
{
	for (unsigned int index = 0; index < this->nButton; index++)
	{
		bool saveActive = this->vActive[index];
		bool saveHover = this->vHover[index];

		if (
			mouseX >= double(this->vStyle[index].pos.x) &&
			mouseX <= double(this->vStyle[index].pos.x + this->vStyle[index].size.width) &&
			mouseY <= this->vStyle[index].pos.y &&
			mouseY >= this->vStyle[index].pos.y - this->vStyle[index].size.height
		)
		{
			this->vActive[index] = LBM;
			this->vHover[index] = true;
		}
		else
		{
			this->vHover[index] = false;
			this->vActive[index] = false;
		}

		if (this->vHover[index] != saveHover || this->vActive[index] != saveActive)
		{
			this->flagCompileVAO = true;
		}
	}

	if (this->flagCompileVAO)
	{
		this->flagCompileVAO = false;
		this->compileVAO();
	}
}

void Button::render()
{
	if (this->flagCompileVAO)
	{
		this->flagCompileVAO = false;
		this->compileVAO();
	}

	vao::bind(this->vaoID);
	vao::draw(TRIANGLE, 0, this->nButton * 6);
}