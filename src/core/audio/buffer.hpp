#include "audio.hpp"
#include <vector>

struct audio::buffer
{
private:
	static std::vector<unsigned int> id;

public:
	static unsigned int create(const char* path);

	static void Delete(unsigned int buffer);
	static void DeleteALL();
};

//class audio::Buffer : private audio::buffer
//{
//
//};