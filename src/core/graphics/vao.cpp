#include "vao.h"
#include "../util/vector.h"
#include "../util/array.h"
#include "../file/obj.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>

// настройка obj компилятора (не менять)
#define N_FLOAT_CORD_TO_VERT 3
#define N_FLOAT_NORMAL_TO_VERT 3
#define N_FLOAT_TEXTURE_CORD_TO_VERT 2

std::vector<unsigned int> vao::id;
unsigned int saveID;

void vao::bind(unsigned int id)
{
    //if (id != saveID)
    //{
    //    if (vector::searchElemntForValue(vao::id, id) == -1)
    //    {
    //        std::cerr << "FAILED: not found VAO width id: " << id << std::endl;
    //        throw "FAILED_BIND_VAO";
    //    }
    //}
    glBindVertexArray(id);
    saveID = id;
}

std::vector<float> vao::FileOBJtoVVO(const char* pathToObj, bool normal, bool textCoord)
{
    std::vector<float> v;
    std::vector<float> v_n;
    std::vector<float> v_t;
    std::vector<float> result;
    std::vector<int> f;

    obj::load(v, f, v_n, v_t, pathToObj);

    unsigned int n_element = N_FLOAT_CORD_TO_VERT;
    if (normal) n_element += N_FLOAT_NORMAL_TO_VERT;
    if (textCoord) n_element += N_FLOAT_TEXTURE_CORD_TO_VERT;

    for (unsigned int vert = 0; vert < f.size() / 9; vert += 1)
    {
        int nVertex[] = { f[vert * 9] - 1, f[vert * 9 + 3] - 1, f[vert * 9 + 6] - 1 };

        for (unsigned int n = 0; n < 3; n++)
        {
            result.push_back(v[nVertex[n] * N_FLOAT_CORD_TO_VERT]);
            result.push_back(v[nVertex[n] * N_FLOAT_CORD_TO_VERT + 1]);
            result.push_back(v[nVertex[n] * N_FLOAT_CORD_TO_VERT + 2]);
        }
    }
    return result;
}

float* vao::FileOBJtoVAO(const char* pathToObj, int& sizeArray, bool normal, bool textCoord)
{
    std::vector<float> vec = vao::FileOBJtoVVO(pathToObj, normal, textCoord);
    sizeArray = vec.size();
    size_t size;
    return array::vectorToArray(vec, size);
}

std::vector<float> vao::addElementToVVO(std::vector<float> data, int n_elementForVert, std::vector<float> democratedData, int n_democratedElementForVert)
{
    std::vector<float> new_vectore;

    const unsigned char finishVertIndex = n_elementForVert + n_democratedElementForVert;
    const unsigned int finishElementIndex = data.size() + democratedData.size();

    unsigned int i = 0, finish_i = n_elementForVert;
    unsigned int j = 0, finish_j = n_democratedElementForVert;

    for (unsigned int index = 0; index < finishElementIndex; index += finishVertIndex)
    {
        while (i < finish_i)
        {
            new_vectore.push_back(data[i]);
            i++;
        }

        while (j < finish_j)
        {
            new_vectore.push_back(democratedData[j]);
            j++;
        }
        
        finish_i += n_elementForVert;
        finish_j += n_democratedElementForVert;
    }

    return new_vectore;
}

unsigned int vao::create(float* data, int sizeOfByte)
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

    //for (int i = 0; i < sizeOfByte; i++)
    //{
    //    std::cout << i << " : " << data[i] << std::endl;
    //}

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

void vao::DeleteALL()
{
    for (int i = 0; i < vao::id.size(); i++)
    {
        glDeleteVertexArrays(1, &vao::id[i]);
        vao::id[i] = 0;
    }
}

void vao::draw(primitive Primitive, int first_vert, int count_vert)
{
    glDrawArrays(Primitive, first_vert, count_vert);
}

void vao::draw(primitive Primitive, unsigned int VAO, int first_vert, int count_vert)
{
    bind(VAO);
    glDrawArrays(Primitive, first_vert, count_vert);
    bind(0);
}