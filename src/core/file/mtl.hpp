#pragma once

#include <vector>
#include <string>

struct mtl
{
	static std::vector<unsigned char*> pathToTexture;
	static std::vector<std::string> nameResources;

	static void load(const char* path);
	static void Delete();
};