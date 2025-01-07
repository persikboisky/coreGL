#include "shader.h"
#include "../load/file.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

std::vector<unsigned int> IDshaderProgramm;
unsigned int selectID;

unsigned int shader::create(const char* vertex_file, const char* fragment_file)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int infoLogLength;

    std::string code = file::read(vertex_file);
    const char* pointer = code.c_str();

    glShaderSource(vertexShaderID, 1, &pointer, NULL);
    glCompileShader(vertexShaderID);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, errorMessage);
        std::cerr << errorMessage;
        delete[] errorMessage;
        throw "FAILED_COMPILE_VERTEX_SHADER";
    }
    else
    {
        std::cout << "OK compile shader: " << vertex_file << std::endl;
    }

    code = file::read(fragment_file);
    pointer = code.c_str();

    glShaderSource(fragmentShaderID, 1, &pointer, NULL);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, errorMessage);
        std::cout << errorMessage;
        delete[] errorMessage;
        throw "FAILED_COMPILE_FRAGMENT_SHADER";
    }
    else
    {
        std::cout << "OK compile shader: " << fragment_file << std::endl;
    }

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);
        std::cout << errorMessage;
        delete[] errorMessage;
        throw "FAILED_LINK_SHADER_PROGRAM";
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    IDshaderProgramm.push_back(programID);
    return programID;
}
void shader::use(unsigned int id)
{
    selectID = id;
    glUseProgram(id);
}

void shader::Delete(unsigned int id)
{
    glDeleteProgram(id);
}

void shader::DeleteALL()
{
    for (unsigned int n = 0; n < IDshaderProgramm.size(); n++)
    {
        glDeleteProgram(IDshaderProgramm[n]);
    }
}

void shader::setValueUniform(const float value, const char* name)
{
    GLint locate = glGetUniformLocation(selectID, name);
    if (locate >= 0)
    {
        glUniform1f(locate, GLfloat(value));
    }
    else
    {
        std::cerr << "Failed locate Uniform: " << name << std::endl;
    }
}

void shader::setValueUniform(glm::mat4 matrix, const char* name)
{
    GLint locate = glGetUniformLocation(selectID, name);
    if (locate >= 0)
    {
        glUniformMatrix4fv(locate, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    else
    {
        std::cerr << "Failed locate Uniform: " << name << std::endl;
    }
}
