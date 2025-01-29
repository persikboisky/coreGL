#ifndef SRC_CORE_GRAPHICS_VAO_H_
#define SRC_CORE_GRAPHICS_VAO_H_

#include <vector>

enum primitive;

struct vao
{
private:
	static std::vector<unsigned int> id;
	static void bind(unsigned int id);

public:
	static unsigned int create(float vert[], int sizeOfFloat);
	static void addAttribute(unsigned int id, int index, int n, int size, int indentation);

	static void Delete(unsigned int id);
	static void DeleteAll();

	static void draw(primitive Primitive, unsigned int id, int first_vert, int count_vert);
};

#endif // !SRC_CORE_GRAPHICS_VAO_H_
