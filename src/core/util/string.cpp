#include "string.hpp"
#include "../file/text.hpp"
#include <string>
#include <iostream>

const std::string end = "\n";

std::string search(std::string file_serch, std::string file_code)
{
	std::string result = "";

	int search_index_element = 0;
	int start_index_string = 0;

	bool Continue = 0;
	bool write = false;

	for (int i = 0; i < file_code.size(); i++)
	{
		if (write == true)
		{
			for (int j = start_index_string; j < file_code.size(); j++)
			{
				if (file_code[j] == end[0])
				{
					std::cout << std::endl;
					break;
				}
				result += file_code[j];
			}
			break;
		}

		if (file_code[i] == file_serch[search_index_element])
		{
			start_index_string = i;
			for (int j = 0; j < file_serch.size(); j++)
			{
				if (file_code[i + j] == file_serch[j])
				{
					if (j == file_serch.size() - 1) write = true;
				}
				else
				{
					Continue = true;
					break;
				}
			}
			if (Continue)
			{
				Continue = false;
				continue;
			}
		}
	}
	return result;
}

std::string string::searchFromString(std::string search_string, std::string string)
{
	return search(search_string, string);
}

std::string string::searchFromFile(std::string search_string, const char* path)
{
	std::string code = text::load(path);
	const char* Code = code.c_str();
	return searchFromString(search_string, Code);
}