#include "audio.h"
#include <vector>

struct audio::buffer
{
private:
	static std::vector<unsigned int> id;

public:
	static unsigned int create(const char* path);

	static void Delete(unsigned int id);
	static void DeleteALL();
};

class audio::Buffer : private audio::buffer
{

};