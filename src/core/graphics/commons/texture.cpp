#include "texture.hpp"
#include "../../util/vector.hpp"
#include "../../file/png.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

extern bool coreInfo;

#pragma region texture
std::vector<unsigned int> texture::id;

void texture::bind(unsigned int id, unsigned int Sample)
{
    glActiveTexture(GL_TEXTURE0 + Sample);
    glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int texture::load(unsigned char* image, int width, int height, int channels)
{
    //glActiveTexture(GL_TEXTURE0);
    GLuint Texture;
    glGenTextures(1, &Texture);

    bool flag = true;
    int index = vector::searchElemntForValue(id, 0);

    if (index != -1 && Texture != 0)
    {
        id[index] = Texture;
        flag = false;
    }

    if (flag)
    {
        if (Texture != 0)
        {
            texture::id.push_back(Texture);
            if (coreInfo) std::cout << "[" << glfwGetTime() << "] " <<
                "OK: create texture id = " << Texture << std::endl;
        }
        else
        {
            std::cerr << "Failed create Texture" << "\n";
            throw "FAILED_CREATE_VAO";
        }
    }

    bind(Texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    switch (channels)
    {
    case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //(GL_LINEAR, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //(GL_LINEAR, GL_NEAREST)

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    bind(0);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return Texture;
}

unsigned int texture::load(std::vector<unsigned char>& png_code, int width, int height, int channels)
{
    return texture::load(png_code.data(), width, height, channels);
}

unsigned int texture::load(const char* path)
{
    int t_width;
    int t_height;
    int t_channels;

    unsigned char* text = png::load(path, t_width, t_height, t_channels);
    unsigned int texture_id = load(text, t_width, t_height, t_channels);

    png::Delete(text);

    return texture_id;
}

void texture::Delete(unsigned int id)
{
    glDeleteTextures(1, &id);
}

void texture::DeleteALL()
{
    for (int i = 0; i < id.size(); i++)
    {
        glDeleteTextures(1, &id[i]);
        //id[i] = 0;
        id.clear();
    }
}
#pragma endregion texture

#pragma region Texture
Texture::Texture(unsigned char* png_code, int width, int height, int channels)
{
    this->id = texture::load(png_code, width, height, channels);
}

Texture::Texture(std::vector<unsigned char>& png_code, int width, int height, int channels)
{
    this->id = texture::load(png_code.data(), width, height, channels);
}

Texture::Texture(const char* path)
{
    this->id = texture::load(path);
}

Texture::~Texture()
{
    texture::Delete(this->id);
}

void Texture::bind(unsigned int Sample) const
{
    texture::bind(this->id, Sample);
}

#pragma endregion Texture