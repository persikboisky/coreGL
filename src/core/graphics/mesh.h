#pragma once
#include <vector>

struct mesh
{
private:
	static std::vector<unsigned int> vao;
	static std::vector<unsigned int> shader;
	static std::vector<unsigned int> texture;
	static std::vector<unsigned int> meshID;

protected:
	static unsigned int selectMesh;
	static unsigned int selectVAO;
	static unsigned int selectShader;
	static unsigned int selectTexture;

public:
	static unsigned int create(const char* path, unsigned int shader);
};

class Mesh : private mesh
{

};