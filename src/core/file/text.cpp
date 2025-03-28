#include "text.hpp"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

extern bool coreInfo;

std::string text::load(const char* path)
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

    if (coreInfo) std::cout << "[" <<  glfwGetTime() << "] " 
        << "OK: read file: " << path << std::endl;
    return text;
}