#ifndef SRC_CORE_GRAPHICS_VAO_HPP_
#define SRC_CORE_GRAPHICS_VAO_HPP_

#include <vector>

enum primitive;

struct vao
{
private:
	static std::vector<unsigned int> id;
	static unsigned int selectID;

protected:
	static unsigned int getSelectId();

public:
	static void bind(unsigned int id);

	static std::vector<float> FileOBJtoVVO(const char* pathToObj, bool normal = false, bool textCoord = false);
	static float* FileOBJtoVAO(const char* pathToObj, int& sizeArray, bool normal, bool textCoord);

	static std::vector<float> addElementToVVO(std::vector<float> data, int n_elementForVert, std::vector<float> democratedData, int n_democratedElementForVert);
	static float* addElementToVAO(float* data, int size_data, int n_elementForVert, float* democratedData, int size_democratedData, int n_democratedElementForVert, int& size_VAO);

	static unsigned int create(float* data, int sizeOfByte);
	static unsigned int create(std::vector<float> data);

	static void addAttribute(unsigned int id, int index, int n, int size, int indentation);

	static void Delete(unsigned int id);
	static void DeleteALL();

	static void draw(primitive Primitive, int first_vert, int count_vert);
	static void draw(primitive Primitive, unsigned int VAO, int first_vert, int count_vert);
};

class VAO: private vao
{
private:
	unsigned int id = 0;
	unsigned int elementToVert;
	int size;
	void bind();

public:
	VAO(float* data, int sizeOfByte, int elementToVert);
	VAO(std::vector<float> data, int elementToVert);
	~VAO();

	void addAttribute(int index, int n, int indentation);
	void draw(primitive Primitive, int first_vert = 0, int count_vert = 0);
};

#endif // !SRC_CORE_GRAPHICS_VAO_HPP_
