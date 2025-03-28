#include "png.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

extern bool coreInfo;

int png::width;
int png::height;
int png::channels;

unsigned char* png::load(const char* path, int& width, int& height, int& channels)
{
	unsigned char* image = stbi_load(path, &png::width, &png::height, &png::channels, STBI_default);
	if (image == 0)
	{
		std::cerr << "FAILED load png: " << path << std::endl;
		throw "FAILED_LOAD_PNG_FILE";
	}

	if (coreInfo) {
		std::cout << "[" << glfwGetTime() << "] " << "OK: load png: " 
			<< path << std::endl;
	}

	width = png::width;
	height = png::height;
	channels = png::channels;

	return image;
}

unsigned char* png::load(const char* path)
{
	return png::load(path, width, height, channels);
}

void png::Delete(unsigned char* PNG)
{
	stbi_image_free(PNG);
}

unsigned char* png::myLoader(const char* path, int& width, int& height, int& channels)
{

}