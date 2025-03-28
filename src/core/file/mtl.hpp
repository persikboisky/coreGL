#pragma once

#include <vector>
#include <list>
#include <string>

struct mtl
{
	static std::vector<unsigned char*> pathToTexture;
	static std::list<std::string> nameResources;

	static void load(const char* path);
	static void Delete();
};