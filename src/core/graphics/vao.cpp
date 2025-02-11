#include "vao.h"
#include "../util/vector.h"
#include "../file/obj.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>

std::vector<unsigned int> vao::id;

void vao::bind(unsigned int id)
{
    // if (id > vao::id.size())
    //{
    //     std::cerr << "Failed bind vao: " << id << "\n";
    //     throw "FAILED_BIND_VAO";
    // }

    glBindVertexArray(id);
}

std::vector<float> vao::loadFromOBJ(const char* path)
{
    std::vector<float> v;
    std::vector<int> f;
    std::vector<float> result;
    obj::load(v, f, path);
    for (unsigned int vert = 0; vert < f.size() / 9; vert++)
    {
        int nVertex1 = f[vert * 9] - 1;
        int nVertex2 = f[vert * 9 + 3] - 1;
        int nVertex3 = f[vert * 9 + 6] - 1;
        //std::cout << nVertex1 << nVertex2 << nVertex3 << std::endl;
        //std::cout << v[2 * 3] << " : " << v[2 * 3 + 1] << " : " << v[2 * 3 + 2] << std::endl;
        
        // вершина 1
        result.push_back(v[nVertex1 * 3]);
        result.push_back(v[nVertex1 * 3 + 1]);
        result.push_back(v[nVertex1 * 3 + 2]);
        // вершина 2
        result.push_back(v[nVertex2 * 3]);
        result.push_back(v[nVertex2 * 3 + 1]);
        result.push_back(v[nVertex2 * 3 + 2]);
        // вершина 3
        result.push_back(v[nVertex3 * 3]);
        result.push_back(v[nVertex3 * 3 + 1]);
        result.push_back(v[nVertex3 * 3 + 2]);
    }
    return result;
}

unsigned int vao::create(float data[], int sizeOfByte)
{
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    bool flag = true;
    int index = vector::searchElemntForValue(vao::id, 0);
    if (index != -1 && VAO != 0)
    {
        vao::id[index] = VAO;
        flag = false;
    }

    if (flag)
    {
        if (VAO != 0)
        {
            vao::id.push_back(VAO);
        }
        else
        {
            std::cerr << "Failed create VAO: " << VAO << "\n";
            throw "FAILED_CREATE_VAO";
        }
    }

    bind(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfByte, data, GL_STATIC_DRAW);
    bind(0);

    return VAO;
}

unsigned int vao::create(std::vector<float> data)
{
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    bool flag = true;
    int index = vector::searchElemntForValue(vao::id, 0);
    if (index != -1 && VAO != 0)
    {
        vao::id[index] = VAO;
        flag = false;
    }

    if (flag)
    {
        if (VAO != 0)
        {
            vao::id.push_back(VAO);
        }
        else
        {
            std::cerr << "Failed create VAO: " << VAO << "\n";
            throw "FAILED_CREATE_VAO";
        }
    }

    bind(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * 4, data.data(), GL_STATIC_DRAW);
    bind(0);

    return VAO;
}

void vao::addAttribute(unsigned int id, int index, int n, int size, int indentation)
{
    bind(id);
    glVertexAttribPointer(
        index, n, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat),
        (GLvoid *)(indentation * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(index);
    bind(0);
}

void vao::Delete(unsigned int id)
{
    if (id < vao::id.size())
    {
        vao::id[vector::searchElemntForValue(vao::id, id)] = 0;
        glDeleteVertexArrays(1, &id);
    }
}

void vao::DeleteAll()
{
    for (int i = 0; i < vao::id.size(); i++)
    {
        glDeleteVertexArrays(1, &vao::id[i]);
        vao::id[i] = 0;
    }
}

void vao::draw(primitive Primitive, unsigned int id, int first_vert, int count_vert)
{
    bind(id);
    glDrawArrays(Primitive, first_vert, count_vert);
    bind(0);
}