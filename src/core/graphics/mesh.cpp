#include "mesh.h"
#include "../file/mtl.h"
#include "../graphics/vao.hpp"
#include <vector>

#pragma mesh

std::vector<unsigned int> mesh::vao;
std::vector<unsigned int> mesh::shader;
std::vector<unsigned int> mesh::texture;
std::vector<unsigned int> mesh::meshID;

unsigned int mesh::create(const char* path, unsigned int shader)
{

}

#pragma Mesh
