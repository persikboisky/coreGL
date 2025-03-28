
#include "shader.hpp"
#include "../../file/text.hpp"
#include "../../util/vector.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <iostream>

extern bool coreInfo;

std::vector<unsigned int> shader::id;
unsigned int shader::SelectID;

std::string VertPath = "";
std::string FragPath = "";

static GLint getLocateUniform(GLuint shader, const char* name)
{
    GLint locate = glGetUniformLocation(shader, name);
    if (locate != -1)
    {
        return locate;
    }
    else
    {
        std::cerr << "Failed locate Uniform: " << name << std::endl;
        throw "Failed locate Uniform";
    }
}

unsigned int shader::getSelectID()
{
    return SelectID;
}

#pragma region CREATE_SHADER
unsigned int shader::createFromCode(const char* codeVert, const char* codeFrag)
{
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int infoLogLength;

    glShaderSource(vertexShaderID, 1, &codeVert, NULL);
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

    if (coreInfo)
    {
        std::cout << "[" << glfwGetTime() << "] " << "OK: compile vertex shader"
            ": " << VertPath << std::endl;
    }

    glShaderSource(fragmentShaderID, 1, &codeFrag, NULL);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, errorMessage);
        std::cerr << errorMessage;
        delete[] errorMessage;
        throw "FAILED_COMPILE_FRAGMENT_SHADER";
    }
    else
    {
        std::cout << "[" << glfwGetTime() << "] " << "OK: compile fragment shader"
            ": " << FragPath << std::endl;
        //std::cout << coreInfo << std::endl;
    }

    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);
        std::cerr << errorMessage;
        delete[] errorMessage;
        throw "FAILED_LINK_SHADER_PROGRAM";
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    std::cout << "[" << glfwGetTime() << "] " << "OK: create shader program, id = "
        << programID << std::endl;

    bool flag = true;
    int index = vector::searchElemntForValue(shader::id, 0);
    if (index != -1 && programID != 0)
    {
        shader::id[index] = programID;
        flag = false;
    }

    if (flag) shader::id.push_back(programID);

    return programID;
}
#pragma endregion CREATE_SHADER

unsigned int shader::createFromFile(const char* pathToVert, const char* pathToFrag)
{
    VertPath = pathToVert;
    FragPath = pathToFrag;

    std::string vert = text::load(pathToVert);
    std::string frag = text::load(pathToFrag);

    return createFromCode(vert.c_str(), frag.c_str());
}   

void shader::use(unsigned int id)
{
    SelectID = id;
    glUseProgram(id);
}

void shader::Delete(unsigned int id)
{
    if (id < shader::id.size())
    {
        shader::id[vector::searchElemntForValue(shader::id, id)] = 0;
        glDeleteProgram(id);
    }
}

void shader::DeleteALL()
{
    for (int i = 0; i < shader::id.size(); i++)
    {
        glDeleteProgram(shader::id[i]);
        shader::id[i] = 0;
    }
}

void shader::UniformMat4(glm::mat4 matrix, const char* name)
{
    glUniformMatrix4fv(getLocateUniform(shader::SelectID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void shader::Uniform1F(const float value, const char* name)
{
    glUniform1f(getLocateUniform(shader::SelectID, name), GLfloat(value));
}

void shader::Uniform2F(glm::vec2 vec2, const char* name)
{
    glUniform2f(getLocateUniform(shader::SelectID, name), vec2.x, vec2.y);
}

void shader::Uniform3F(glm::vec3 vec3, const char* name)
{
    glUniform3f(getLocateUniform(shader::SelectID, name), vec3.x, vec3.y, vec3.z);
}


void shader::Uniform4F(glm::vec4 vec4, const char* name)
{
    glUniform4f(getLocateUniform(shader::SelectID, name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void shader::Uniform1I(glm::ivec1 value, const char* name)
{
    glUniform1i(getLocateUniform(shader::SelectID, name), value.x);
}

void shader::Uniform2I(glm::ivec2 value, const char* name)
{
    glUniform2i(getLocateUniform(shader::SelectID, name), value.x, value.y);
}

Shader::Shader(const char* pathVert, const char* pathFrag)
{
    this->id = shader::createFromFile(pathVert, pathFrag);
}

Shader::~Shader()
{
    shader::Delete(this->id);
}

void Shader::use() const
{
    shader::use(this->id);
}

void Shader::UniformMat4(glm::mat4 matrix, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::UniformMat4(matrix, name);
}

void Shader::Uniform1F(const float value, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::Uniform1F(value, name);
}

void Shader::Uniform2F(glm::vec2 vec2, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::Uniform2F(vec2, name);
}

void Shader::Uniform3F(glm::vec3 vec3, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::Uniform3F(vec3, name);
}

void Shader::Uniform4F(glm::vec4 vec4, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::Uniform4F(vec4, name);
}

void Shader::Uniform1I(glm::ivec1 ivec1, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::Uniform1I(ivec1, name);
}

void Shader::Uniform2I(glm::ivec2 ivec2, const char* name) const
{
    if (shader::getSelectID() != this->id) this->use();
    shader::Uniform2I(ivec2, name);
}