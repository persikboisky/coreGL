#include "font.hpp"
#include "../commons/texture.hpp"
#include "../../file/png.hpp"
#include <GL/glew.h>
#include <vector>
#include <string>
#include <iostream>

// путь к шрифтам
constexpr const char* PATH_TO_TEXTURE_FONTS = "./res/fonts/";

// названия атласов
const std::string fileName[5] = { "font_0.png", "font_1.png", "font_2.png", "font_3.png", "font_4.png" };

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