#ifndef SRC_CORE_GRAPHICS_SHADER_H_
#define SRC_CORE_GRAPHICS_SHADER_H_

#include <glm/glm.hpp>
#include <vector>

struct shader
{
private:
	static std::vector<unsigned int> id;
	static unsigned int SelectID;

public:
	static unsigned int createFromCode(const char* codeVert, const char* codeFrag);
	static unsigned int createFromFile(const char* pathVert, const char* pathFrag);

	static void use(unsigned int id);

	static void setValueUniform(const float value, const char* name);
    static void setValueUniform(glm::mat4 matrix, const char* name);

	static void Delete(unsigned int id);
	static void DeleteALL();
};

#endif // !SRC_CORE_GRAPHICS_SHADER_H_
