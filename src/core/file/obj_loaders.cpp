#include "obj_loaders.hpp"
#include "text.hpp"
#include "mtl.hpp"
#include <vector>
#include <string>
#include <iostream>
//#include <Windows.h>

extern bool coreInfo;

const std::string specSymbol = "\n";

//static std::string loadStringFromVert(unsigned int& index, std::string fileCode)
//{
//	std::string str = "";
//	for (unsigned int index_2 = index + 1;; index_2++)
//	{
//		if (fileCode[index_2] == '\n')
//		{
//			index = index_2;
//			std::cout << index_2 << std::endl;
//			break;
//		}
//		str += fileCode[index_2];
//	}
//	return str;
//}

bool obj_loaders::mtl = true;

void obj_loaders::load(std::vector<float> &vert, std::vector<int> &face, std::vector<float>& vert_normal, std::vector<float> &coord_texture, const char* path)
{
	mtl = true;
	std::string pathToMtl = path;
	pathToMtl.replace(pathToMtl.size() - 3, pathToMtl.size() - 1, "mtl");
	//std::cout << pathToMtl << std::endl;
	try
	{
		mtl::load(pathToMtl.c_str());
	}
	catch (...)
	{
		mtl = false;
	}

	unsigned int selectResourceFromMtl = 0;

	std::string fileCode = text::load(path);
	std::string vertStr = "";
	for (unsigned int index = 0; index < fileCode.length() - 1; index++)
	{
		if (fileCode[index] == 'v' && fileCode[index + 1] == ' ')
		{
			for (unsigned int index_2 = index + 2;; index_2++)
			{
				if (fileCode[index_2] == specSymbol[0])
				{
					index = index_2;
					break;
				}
				vertStr += fileCode[index_2];
			}

			//vertStr += loadStringFromVert(index, fileCode);

			std::string result = "";
			for (unsigned int index_3 = 0; index_3 < vertStr.length(); index_3++)
			{
				if (vertStr[index_3] != ' ')
				{
					for (unsigned int i = index_3; i < vertStr.length() + 1; i++)
					{
						if (vertStr[i] == ' ' || vertStr[i] == specSymbol[0] || i == vertStr.length())
						{
							//std::cout << std::stof(result) << std::endl;
							vert.push_back(std::stof(result));
							result = "";
							continue;
						}

						result += vertStr[i];
						index_3 = i;
					}
				}
			}
			vertStr = "";
		}
		else if (fileCode[index] == 'v' && fileCode[index + 1] == 'n')
		{
			for (unsigned int index_2 = index + 2;; index_2++)
			{
				if (fileCode[index_2] == specSymbol[0])
				{
					index = index_2;
					break;
				}
				vertStr += fileCode[index_2];
			}

			std::string result = "";
			for (unsigned int index_3 = 0; index_3 < vertStr.length(); index_3++)
			{
				if (vertStr[index_3] != ' ')
				{
					for (unsigned int i = index_3; i < vertStr.length() + 1; i++)
					{
						if (vertStr[i] == ' ' || vertStr[i] == specSymbol[0] || i == vertStr.length())
						{
							vert_normal.push_back(std::stof(result));
							//std::cout << std::stof(result) << std::endl;
							result = "";
							continue;
						}

						result += vertStr[i];
						index_3 = i;
					}
				}
			}
			vertStr = "";
		}
		else if (fileCode[index] == 'v' && fileCode[index + 1] == 't')
		{
			for (unsigned int index_2 = index + 2;; index_2++)
			{
				//std::cout << fileCode[index_2];
				//Sleep(10);

				if (fileCode[index_2] == specSymbol[0])
				{
					index = index_2;
					break;
				}
				vertStr += fileCode[index_2];
			}
			std::string result = "";
			for (unsigned int index_3 = 0; index_3 < vertStr.length(); index_3++)
			{
				if (vertStr[index_3] != ' ')
				{
					for (unsigned int i = index_3; i < vertStr.length() + 1; i++)
					{
						if (vertStr[i] == ' ' || vertStr[i] == specSymbol[0] || i == vertStr.length())
						{
							coord_texture.push_back(std::stof(result));
							//std::cout << std::stof(result) << std::endl;
							result = "";
							continue;
						}

						result += vertStr[i];
						index_3 = i;
					}
				}
			}
			//std::cout << fileCode[index] << std::endl;
			vertStr = "";
		}
		else if (fileCode[index] == 'f' && fileCode[index + 1] == ' ')
		{
			for (unsigned int index_2 = index + 1;; index_2++)
			{
				if (fileCode[index_2] == specSymbol[0])
				{
					index = index_2;
					break;
				}
				vertStr += fileCode[index_2];
			}

			std::string result = "";
			for (unsigned int index_3 = 0; index_3 < vertStr.length(); index_3++)
			{
				if (vertStr[index_3] != ' ')
				{
					for (unsigned int i = index_3; i < vertStr.length() + 1; i++)
					{
						if (vertStr[i] == '/' && vertStr[i + 1] == '/')
						{
							face.push_back(std::stof(result));
							face.push_back(0);
							std::cout << result << std::endl;
							i++;
							result = "";
							continue;
						}
						else if (vertStr[i] == '/' || vertStr[i] == ' ' || vertStr[i] == specSymbol[0] || i == vertStr.length())
						{
							//std::cout << result << std::endl;
							face.push_back(std::stof(result));
							result = "";
							continue;
						}

						result += vertStr[i];
						index_3 = i;
					}
				}
			}
			vertStr = "";
		}
		else;
	}
	//std::cout << vert[4] << std::endl;
	if (coreInfo) std::cout << "OK: compile object, paligons: " << face.size() / 9 << ", path: " << path << std::endl;
	//throw "f";
}