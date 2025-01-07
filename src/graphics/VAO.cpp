#include "vao.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> listVAO;

void vao::bind(unsigned int id)
{
    if (id > listVAO.size())
    {
        std::cerr << "Failed bind vao: " << id << "\n";
        throw "FAILED_BIND_VAO";
    }
    glBindVertexArray(id);
}

unsigned int vao::create(float data[], int sizeOfByte)
{
    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    if (VAO != 0) 
    {
        listVAO.push_back(VAO);
    }
    else
    {
        std::cerr << "Failed create VAO: " << VAO << "\n";
        throw "FAILED_CREATE_VAO";
    }

    bind(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeOfByte, data, GL_STATIC_DRAW);
    bind(0);

    return VAO;
}

void vao::addAttribute(unsigned int id, int index, int n, int size, int indentation)
{
    bind(id);
    glVertexAttribPointer(index, n, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)(indentation * sizeof(GLfloat)));
    glEnableVertexAttribArray(index);
    bind(0);
}

void vao::draw(primitiveENUM primitive, unsigned int id, int first_vert, int finish_vert)
{
    bind(id);
    glDrawArrays(primitive, first_vert, finish_vert);
    bind(0);
}

void vao::Delete(unsigned int id)
{
    glDeleteVertexArrays(1, &id);
}

void vao::DeleteALL()
{
    for (unsigned int n = 0; n < listVAO.size(); n++)
    {
        glDeleteVertexArrays(1, &listVAO[n]);
    }
}