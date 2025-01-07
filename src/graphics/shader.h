#ifndef SRC_GRAPHICS_SHADER_H_
#define SRC_GRAPHICS_SHADER_H_

#include <glm/glm.hpp>

struct shader
{
    static unsigned int create(const char* path_vert, const char* path_frag);
    static void use(unsigned int id);
    static void Delete(unsigned int id);
    static void DeleteALL();
    static void setValueUniform(const float value, const char* name);
    static void setValueUniform(glm::mat4 matrix, const char* name);
};

#endif // !SRC_GRAPHICS_SHADER_H_
