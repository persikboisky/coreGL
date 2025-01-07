#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

#include "PNG.h"

int png::width, png::height, png::channels;

unsigned char* png::load(const char* PATH, int& Width, int& Height, int& Channels)
{
	unsigned char* image = stbi_load(PATH, &png::width, &png::height, &png::channels, STBI_default);

	Width = width;
	Height = height;
	Channels = channels;

	if (image != 0) {
		std::cout << "OK load png: " << PATH << std::endl;
	}
	else
	{
		std::cerr << "FAILED load png: " << PATH << std::endl;
	}
	return image;
}

void png::Delete(unsigned char* PNG)
{
	stbi_image_free(PNG);
}