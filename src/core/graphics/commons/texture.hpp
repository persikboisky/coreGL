#include <vector>

struct texture
{
private:
    static std::vector<unsigned int> id;

public:
    static void bind(unsigned int id, unsigned int Sample = 0);

    static unsigned int load(unsigned char* png_code, int width, int height, int channels);
    static unsigned int load(std::vector<unsigned char>& png_code, int width, int height, int channels);
    static unsigned int load(const char* path);

    static void Delete(unsigned int id);
    static void DeleteALL();
};

class Texture : private texture
{
private:
    unsigned int id;

public:
    Texture(unsigned char* png_code, int width, int height, int channels);
    Texture(std::vector<unsigned char>& png_code, int width, int height, int channels);
    Texture(const char* path);
    ~Texture();

    void bind(unsigned int Sample = 0) const;
};