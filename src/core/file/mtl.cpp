#include "mtl.hpp"
#include "text.hpp"
#include <vector>
#include <list>
#include <string>
#include <iostream>

extern bool coreInfo;

std::vector<unsigned char*> mtl::pathToTexture;
std::list<std::string> mtl::nameResources;

void mtl::load(const char* path)
{
	std::string code = text::load(path);

	for (unsigned int index = 0; index < code.size(); index++)
	{
		if (code[index] == 'n' && code[index + 1] == 'e' && code[index + 2] == 'w')
		{
			std::string name = "";
			for (unsigned int index_2 = index + 7;; index_2++)
			{
				if (code[index_2] == '\n')
				{
					mtl::nameResources.push_back(name);
					std::cout << name << std::endl;
					index = index_2;
					break;
				}
				name += code[index_2];
			}
		}
	}
}

void mtl::Delete()
{
	mtl::pathToTexture.clear();
	mtl::nameResources.clear();
}