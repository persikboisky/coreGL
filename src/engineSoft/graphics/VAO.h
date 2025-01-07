#ifndef SRC_GRAPHICS_VAO_H_
#define SRC_GRAPHICS_VAO_H_

enum primitiveENUM
{
    TRIANGLE = 0x0004,
    POINT = 0x0000,
    QUADS = 0x0007,
    POLYGON = 0x0009
};

struct vao
{
    static void bind(unsigned int id);
    static unsigned int create(float data[], int sizeOfByte);
    static void addAttribute(unsigned int id, int index, int n, int size, int indentation);
    static void draw(primitiveENUM primitive, unsigned int id, int first_vert, int finish_vert);
    static void Delete(unsigned int id);
    static void DeleteALL();
};


#endif //SRC_GRAPHICS_VAO_H_