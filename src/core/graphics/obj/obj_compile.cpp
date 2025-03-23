#include "obj_compile.hpp"
#include "../../file/obj_loaders.hpp"
#include <vector>
#include <iostream>

// настройка obj компилятора (не изменять параметры)
#define N_ELEMENT_TO_FACE 3
#define N_ELEMENT_TO_VERT 3
#define N_ELEMENT_TO_NORMAL_VERT 3
#define N_ELEMENT_TO_TEXTURE_VERT 2

std::vector<float> obj_compile::compileToVAO(const char* pathToObj, bool normal, bool textCoord)
{
    std::vector<float> result;
    std::vector<float> v;
    std::vector<float> v_n;
    std::vector<float> v_t;
    std::vector<int> f;
 
    obj_loaders::load(v, f, v_n, v_t, pathToObj);

    for (unsigned int index = 0; index < f.size() / N_ELEMENT_TO_FACE; index++)
    {
        unsigned int v_index = f[index * N_ELEMENT_TO_FACE] - 1;
        result.push_back(v[v_index * N_ELEMENT_TO_VERT]);
        result.push_back(v[v_index * N_ELEMENT_TO_VERT + 1]);
        result.push_back(v[v_index * N_ELEMENT_TO_VERT + 2]);

        if (normal)
        {
            unsigned int vn_index = f[index * N_ELEMENT_TO_FACE + 2] - 1;
            //std::cout << v_n[vn_index * N_ELEMENT_TO_NORMAL_VERT] << std::endl;
            result.push_back(v_n[vn_index * N_ELEMENT_TO_NORMAL_VERT]);
            result.push_back(v_n[vn_index * N_ELEMENT_TO_NORMAL_VERT + 1]);
            result.push_back(v_n[vn_index * N_ELEMENT_TO_NORMAL_VERT + 2]);
        }
    }

    return result;
}