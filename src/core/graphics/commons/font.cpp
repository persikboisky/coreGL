#include "font.hpp"
#include "../commons/vao.hpp"
#include "../commons/shader.hpp"
#include "../commons/texture.hpp"
#include "../../file/png.hpp"
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <iostream>

// путь к шейдерам шрифтов
constexpr const char* PATH_TO_VERTEX_SHADER = "./res/fonts/main_font_v.glsl";
constexpr const char* PATH_TO_FRAGMENT_SHADER = "./res/fonts/main_font_f.glsl";

// путь к атласам шрифтов
constexpr const char* PATH_TO_TEXTURE_FONTS = "./res/fonts/";

// названия атласов шрифтов
const std::string fileName[5] = { "font_0.png", "font_1.png", "font_2.png", "font_3.png", "font_4.png" };

enum primitive
{
	TRIANGLE = GL_TRIANGLES
};

static void addPoligon(
	std::vector<float> &buffer,
	glm::vec2 pos,
	glm::vec2 size,
	glm::vec2 t_coord,
	glm::vec2 t_size,
	glm::vec4 color
)
{
	// первая вершина
	buffer.push_back(pos.x);
	buffer.push_back(pos.y);

	buffer.push_back(t_coord.x);
	buffer.push_back(t_coord.y);

	buffer.push_back(color.x);
	buffer.push_back(color.y);
	buffer.push_back(color.z);
	buffer.push_back(color.w);

	// вторая вершина
	buffer.push_back(pos.x);
	buffer.push_back(pos.y - size.y);

	buffer.push_back(t_coord.x);
	buffer.push_back(t_coord.y + t_size.y);

	buffer.push_back(color.x);
	buffer.push_back(color.y);
	buffer.push_back(color.z);
	buffer.push_back(color.w);

	// третья вершина
	buffer.push_back(pos.x + size.x);
	buffer.push_back(pos.y - size.y);

	buffer.push_back(t_coord.x + t_size.x);
	buffer.push_back(t_coord.y + t_size.y);

	buffer.push_back(color.x);
	buffer.push_back(color.y);
	buffer.push_back(color.z);
	buffer.push_back(color.w);

	// четвёртая вершина
	buffer.push_back(pos.x);
	buffer.push_back(pos.y);

	buffer.push_back(t_coord.x);
	buffer.push_back(t_coord.y);

	buffer.push_back(color.x);
	buffer.push_back(color.y);
	buffer.push_back(color.z);
	buffer.push_back(color.w);

	// пятая вершина
	buffer.push_back(pos.x + size.x);
	buffer.push_back(pos.y - size.y);

	buffer.push_back(t_coord.x + t_size.x);
	buffer.push_back(t_coord.y + t_size.y);

	buffer.push_back(color.x);
	buffer.push_back(color.y);
	buffer.push_back(color.z);
	buffer.push_back(color.w);

	// шестая вершина
	buffer.push_back(pos.x + size.x);
	buffer.push_back(pos.y);

	buffer.push_back(t_coord.x + t_size.x);
	buffer.push_back(t_coord.y);

	buffer.push_back(color.x);
	buffer.push_back(color.y);
	buffer.push_back(color.z);
	buffer.push_back(color.w);
}

#pragma region font

font::font(const char* name)
{
	std::string path = PATH_TO_TEXTURE_FONTS;
	path += name;

	std::vector<unsigned char> codeTexture;

	int channels = 0;
	int width = 0;
	int height = 0;

	for (unsigned int index = 0; index < 5; index++)
	{
		unsigned char* textureCode = png::load((path + "/" + fileName[index]).c_str());

		if (index == 0)
		{
			channels = png::channels;
			width = png::width;
			height = png::height;
		}
		else
		{
			if (png::channels != channels)
			{
				std::cerr << "FAILED_NO_EQUAL_CHANNELS_TO_FONTS_PNG" << std::endl;
				throw "FAILED_NO_EQUAL_CHANNELS_TO_FONTS_PNG";
			}
			if (png::width != width)
			{
				std::cerr << "FAILED_NO_EQUAL_WIDTH_TO_FONTS_PNG" << std::endl;
				throw "FAILED_NO_EQUAL_WIDTH_TO_FONTS_PNG";
			}
			if (png::height != height)
			{
				std::cerr << "FAILED_NO_EQUAL_HEIGHT_TO_FONTS_PNG" << std::endl;
				throw "FAILED_NO_EQUAL_HEIGHT_TO_FONTS_PNG";
			}
		}

		for (unsigned int index_2 = 0; index_2 < png::width * png::height * png::channels; index_2++)
		{
			codeTexture.push_back(textureCode[index_2]);
		}
	}

	this->textureFont = new Texture(codeTexture, png::width, png::height * 5, png::channels);

	this->widthSymbol = 1.0f / 16.0f;
	this->heightSymbol = 1.0f / 5.0f / 16.0f;
	std::cout << this->heightSymbol << std::endl;

	codeTexture.clear();
}

font::~font()
{
	delete this->textureFont;
}
#pragma endregion font

#pragma region BUFFER_TEXT_2D

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
	this->Font = Font;
}

void BufferText2D::addText(std::string text, float x, float y, float width, float height,
	float c_red, float c_green, float c_blue, float c_alpha
)
{
	const unsigned int n_symbol = text.length();
	const float widthSymbol = width / (float)n_symbol;
	const float heightSymbol = widthSymbol;

	for (unsigned int index = 0; index < text.length(); index++)
	{
		int codeSymbol = char16_t(text[index]);

		// это пробел
		if (codeSymbol == 32) continue;

		//std::cout << codeSymbol % 16  << ":" << codeSymbol / 16 << ":" << text[index] << std::endl;

		// работа с атласом font_0
		if (codeSymbol > 0 && codeSymbol < 256) 
		{
			this->n_vertex += 6;
			addPoligon(
				this->vertexes,
				glm::vec2(x + widthSymbol * (float)index, y),
				glm::vec2(widthSymbol, heightSymbol),
				glm::vec2(
					this->Font->widthSymbol * (codeSymbol % 16), 
					this->Font->heightSymbol * (codeSymbol / 16)
				),
				glm::vec2(this->Font->widthSymbol, this->Font->heightSymbol),
				glm::vec4(c_red, c_green, c_blue, c_alpha)
			);
		}
		// работа с атласом font_4
		else if (codeSymbol > 65455 && codeSymbol < 65712)
		{
			codeSymbol -= 64432;
			std::cout << codeSymbol << std::endl;
			this->n_vertex += 6;
			addPoligon(
				this->vertexes,
				glm::vec2(x + widthSymbol * (float)index, y),
				glm::vec2(widthSymbol, heightSymbol),
				glm::vec2(
					this->Font->widthSymbol * (codeSymbol % 16),
					this->Font->heightSymbol * (codeSymbol / 16)
				),
				glm::vec2(this->Font->widthSymbol, this->Font->heightSymbol),
				glm::vec4(c_red, c_green, c_blue, c_alpha)
			);
			std::cout << codeSymbol % 16 << ":" << codeSymbol / 16 << ":" << text[index] << std::endl;
		}
	}
	

	//std::cout << this->Font->widthSymbol << std::endl;

	this->vaoCompile = true;
}

void BufferText2D::DeleteText()
{
	this->n_vertex = 0;
	this->vertexes.clear();
	vao::Delete(this->vao);
	this->vao = 0;
}

void BufferText2D::render()
{
	// компилируем vao
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

	// рисуем
	this->shader2D->use();
	this->Font->textureFont->bind(0);
	this->shader2D->Uniform1I(glm::ivec1(0), "text");
	vao::bind(this->vao);
	vao::draw(TRIANGLE, 0, n_vertex);
}

#pragma endregion BUFFER_TEXT_2D