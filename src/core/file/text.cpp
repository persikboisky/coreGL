#include "text.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string text::read(const char* path)
{
    std::string text = "";
    std::ifstream file(path, std::ios::in);
    if (file.is_open()) 
    {
        std::stringstream sstr;
        sstr << file.rdbuf();
        text = sstr.str();
        file.close();
    }
    else
    {
        std::cerr << "Failed read file: " << path << std::endl;
        throw "FAILED_READ_FILE";
    }

    return text;
}