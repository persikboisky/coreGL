#ifndef SRC_CORE_GRAPHICS_SHADER_H_
#define SRC_CORE_GRAPHICS_SHADER_H_

#include <glm/glm.hpp>
#include <vector>

struct shader
{
private:
	static std::vector<unsigned int> id;
	static unsigned int SelectID;

protected:
	static unsigned int getSelectID();

public:
	static unsigned int createFromCode(const char* codeVert, const char* codeFrag);
	static unsigned int createFromFile(const char* pathVert, const char* pathFrag);

	static void use(unsigned int id);

    static void UniformMat4(glm::mat4 matrix, const char* name);
	static void Uniform1F(const float value, const char* name);
	static void Uniform2F(glm::vec2 vec2, const char* name);
	static void Uniform3F(glm::vec3 vec3, const char* name);
	static void Uniform4F(glm::vec4 vec4, const char* name);

	static void Delete(unsigned int id);
	static void DeleteALL();
};

class Shader : private shader
{
private:
	unsigned int id;

public:
	Shader(const char* pathVert, const char* pathFrag);
	~Shader();

	void use();

	void UniformMat4(glm::mat4 matrix, const char* name);
	void Uniform1F(const float value, const char* name);
	void Uniform2F(glm::vec2 vec2, const char* name);
	void Uniform3F(glm::vec3 vec3, const char* name);
	void Uniform4F(glm::vec4 vec4, const char* name);
};

#endif // !SRC_CORE_GRAPHICS_SHADER_H_
