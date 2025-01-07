#include "file.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string file::read(const char* filename)
{
    std::string text = "";
    std::ifstream file(filename, std::ios::in);
    if (file.is_open())
    {
        std::stringstream sstr;
        sstr << file.rdbuf();
        text = sstr.str();
        file.close();
    }
    else
    {
        std::cerr << "Failed read file: " << filename << std::endl;
        throw "FAILED_READ_FILE";
    }

    file.close();

    return text;
}