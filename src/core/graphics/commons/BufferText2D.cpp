#include "BufferText2D.hpp"
#include "font.hpp"
#include "vao.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "styleText.hpp"
#include "../../util/structs.hpp"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>

// путь к шейдерам для шрифтов
constexpr const char* PATH_TO_VERTEX_SHADER = "./res/fonts/main_font_v.glsl";
constexpr const char* PATH_TO_FRAGMENT_SHADER = "./res/fonts/main_font_f.glsl";

enum primitive
{
	POINT = GL_POINTS,
	TRIANGLE = GL_TRIANGLES,
	LINER = GL_LINES
};

static void addPoligon(
	std::vector<float>& buffer,
	position_2f pos,
	size_2f size,
	position_2f t_coord,
	size_2f t_size,
	color_rgba color,
	glm::mat4 matrix = glm::mat4(1.0f)
)
{
	glm::vec4 pos4f = glm::vec4(pos.x, pos.y, 0.0f, 1.0f) * matrix;
	float finishX = glm::vec4(glm::vec4(pos.x + size.width, pos.y, 0.0f, 1.0f) * matrix).x;
	float finishY = glm::vec4(glm::vec4(pos.x, pos.y - size.height, 0.0f, 1.0f) * matrix).y;

	// первая вершина
	buffer.push_back(pos4f.x);
	buffer.push_back(pos4f.y);

	buffer.push_back(t_coord.x);
	buffer.push_back(t_coord.y);

	buffer.push_back(color.red);
	buffer.push_back(color.green);
	buffer.push_back(color.blue);
	buffer.push_back(color.alpha);

	// вторая вершина
	buffer.push_back(pos4f.x);
	buffer.push_back(finishY);

	buffer.push_back(t_coord.x);
	buffer.push_back(t_coord.y + t_size.height);

	buffer.push_back(color.red);
	buffer.push_back(color.green);
	buffer.push_back(color.blue);
	buffer.push_back(color.alpha);

	// третья
	buffer.push_back(finishX);
	buffer.push_back(finishY);

	buffer.push_back(t_coord.x + t_size.width);
	buffer.push_back(t_coord.y + t_size.height);

	buffer.push_back(color.red);
	buffer.push_back(color.green);
	buffer.push_back(color.blue);
	buffer.push_back(color.alpha);

	// четвёртая
	buffer.push_back(pos4f.x);
	buffer.push_back(pos4f.y);

	buffer.push_back(t_coord.x);
	buffer.push_back(t_coord.y);

	buffer.push_back(color.red);
	buffer.push_back(color.green);
	buffer.push_back(color.blue);
	buffer.push_back(color.alpha);

	// пятая
	buffer.push_back(finishX);
	buffer.push_back(finishY);

	buffer.push_back(t_coord.x + t_size.width);
	buffer.push_back(t_coord.y + t_size.height);

	buffer.push_back(color.red);
	buffer.push_back(color.green);
	buffer.push_back(color.blue);
	buffer.push_back(color.alpha);

	// шестая
	buffer.push_back(finishX);
	buffer.push_back(pos4f.y);

	buffer.push_back(t_coord.x + t_size.width);
	buffer.push_back(t_coord.y);

	buffer.push_back(color.red);
	buffer.push_back(color.green);
	buffer.push_back(color.blue);
	buffer.push_back(color.alpha);
}

Shader* BufferText2D::shader2D = nullptr;
unsigned int BufferText2D::n_Buffer = 0;

BufferText2D::BufferText2D() : Font(nullptr)
{
	if (BufferText2D::shader2D == nullptr)
	{
		BufferText2D::shader2D = new Shader(
			PATH_TO_VERTEX_SHADER,
			PATH_TO_FRAGMENT_SHADER
		);
	}

	BufferText2D::n_Buffer++;
}

BufferText2D::~BufferText2D()
{
	BufferText2D::n_Buffer--;
}

void BufferText2D::linkFont(font& Font)
{
	this->Font = &Font;
}

void BufferText2D::linkFont(font*& Font)
{
	if (Font == nullptr)
	{
		std::cerr << "FAILED_LINK_FONT_FOR_BUFFER_TEXTURE_2D" << std::endl;
		throw "FAILED_LINK_FONT_FOR_BUFFER_TEXTURE_2D";
	}
	this->Font = Font;
}

void BufferText2D::addText(std::string text, float x, float y, float length,
	float RowingBetweenTheSymbols,
	float c_red, float c_green, float c_blue, float c_alpha
)
{
	//float decreaseWidthSymbol = -0.01;
	RowingBetweenTheSymbols /= 500.0f;

	// не забыть доделать:)
	const float decreaseWidthTextureSymbol = 0.03f;
	const float decreaseHeightTextureSymbol = 0.0010f;
	// -------------------------------------

	float rotate = 0.0f;

	const unsigned int n_symbol = text.length();
	const float widthSymbol = (length / (float)n_symbol) - RowingBetweenTheSymbols / 2.0f;
	const float heightSymbol = widthSymbol * 1.75f;// / 1.25f;

	for (unsigned int index = 0; index < text.length(); index++)
	{
		int codeSymbol = char16_t(text[index]);

		// это пробел
		if (codeSymbol == 32) continue;

		//std::cout << codeSymbol % 16  << ":" << codeSymbol / 16 << ":" << text[index] << std::endl;

		// font_0
		if (codeSymbol > -1 && codeSymbol < 256)
		{
			this->n_vertex += 6;
		}
		// font_4
		else if (codeSymbol > 65455 && codeSymbol < 65712)
		{

			codeSymbol -= 64432;
			this->n_vertex += 6;
		}

		position_2f pos = position_2f(x + (widthSymbol + RowingBetweenTheSymbols) * (float)index, y);
		glm::vec4 p = glm::vec4(pos.x, pos.y, 0.0f, 1.0f);

		glm::mat4 matrix = glm::mat4(1.0f);
		/*matrix = glm::rotate(
			matrix,
			glm::radians(90.0f),
			glm::vec3(0, 0, 1)
		);*/
		p = p * matrix;

		pos.x = p.x;
		pos.y = p.y;

		addPoligon(
			this->vertexes,
			pos,
			size_2f(widthSymbol, heightSymbol),
			position_2f(
				this->Font->widthSymbol * (codeSymbol % 16) + 0.00001f,
				this->Font->heightSymbol * (codeSymbol / 16) + decreaseHeightTextureSymbol / 2.0f
			),
			size_2f(
				this->Font->widthSymbol - decreaseWidthTextureSymbol,
				this->Font->heightSymbol - decreaseHeightTextureSymbol
			),
			color_rgba(c_red, c_green, c_blue, c_alpha)
			/*glm::rotate(
				glm::mat4(1.0f),
				glm::radians(10.0f),
				glm::vec3(0, 0, 1)
			)*/
		);
	}


	//std::cout << this->Font->widthSymbol << std::endl;

	this->vaoCompile = true;
}

//inline void BufferText2D::addText(
//	std::string text,
//	position_2f pos,
//	size_2f size,
//	color_rgba color
//)
//{
//	BufferText2D::addText(
//		text, pos.x, pos.y, size.width,
//		color.red, color.green, color.blue, color.alpha
//	);
//}

void BufferText2D::DeleteText()
{
	this->n_vertex = 0;
	this->vertexes.clear();
	vao::Delete(this->vao);
	this->vao = 0;
}

float angle = 0.0f;
void BufferText2D::render()
{
	// ����������� vao
	if (this->vaoCompile == true)
	{
		this->vaoCompile = false;

		if (this->vao != 0)
		{
			vao::Delete(this->vao);
		}

		this->vao = vao::create(this->vertexes);
		vao::addAttribute(this->vao, 0, 2, 8, 0);
		vao::addAttribute(this->vao, 1, 2, 8, 2);
		vao::addAttribute(this->vao, 2, 4, 8, 4);
	}

	// ������
	this->shader2D->use();
	this->Font->textureFont->bind(0);
	this->shader2D->Uniform1I(glm::ivec1(0), "text");
	glm::mat4 matrix = glm::mat4(1.0f);
	//matrix = glm::scale(matrix, glm::vec3(1.5, 1.5, 1));
	//matrix = glm::translate(matrix, glm::vec3(0.4, 0, 0));
	/*matrix = glm::rotate(
		matrix,
		glm::radians(180.0f),
		glm::vec3(0, 0, 1)
	);*/
	this->shader2D->UniformMat4(matrix, "matrix");
	vao::bind(this->vao);
	vao::draw(TRIANGLE, 0, n_vertex);
}