#ifndef SRC_CORE_LOADERS_PNG_H_
#define SRC_CORE_LOADERS_PNG_H_

struct png
{
	static int width;
	static int height;
	static int channels;

	static unsigned char* load(const char* path, int& width, int& height, int& channels);
	static unsigned char* load(const char* path);

	static void Delete(unsigned char* png);
};

#endif // !SRC_CORE_LOADERS_PNG_H_
