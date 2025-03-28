#ifndef SRC_CORE_LOADERS_PNG_HPP_
#define SRC_CORE_LOADERS_PNG_HPP_

struct png
{
	static int width;
	static int height;
	static int channels;

	static unsigned char* load(const char* path, int& width, int& height, int& channels);
	static unsigned char* load(const char* path);

	static void Delete(unsigned char* png);

	static unsigned char* myLoader(const char* path, int& width, int& height, int& channels);
};

#endif // !SRC_CORE_LOADERS_PNG_HPP_
