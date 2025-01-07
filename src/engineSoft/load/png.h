#ifndef SRC_LOAD_PNG_H_
#define SRC_LOAD_PNG_H_

struct png
{
    static int width;
    static int height;
    static int channels;
    static unsigned char* load(const char* PATH, int& Width, int& Height, int& Channels);
    static void Delete(unsigned char* png);
};

#endif // !SRC_LOAD_PNG_H_
