#include <vector>

struct texture
{
private:
    static std::vector<unsigned int> id;

public:
    static void bind(unsigned int id);

    static unsigned int load(unsigned char* png_code, int width, int height, int channels);
    static unsigned int load(const char* path);

    static void Delete(unsigned int id);
    static void DeleteALL();
};

class Texture : private texture
{
private:
    unsigned int id;

public:
    Texture(const char* path);
    ~Texture();
    void bind() const;
};