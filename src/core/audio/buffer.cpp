#define DEBUG false

#include "buffer.h"
#include <AL/alext.h>
#include <iostream>

std::vector<unsigned int> audio::buffer::id;

unsigned int audio::buffer::create(const char* path)
{
	unsigned int buffer;
	alGenBuffers(1, &buffer);

	if (buffer == 0)
	{
		std::cerr << "Failed: create audio buffer" << std::endl;
		throw "FAILED_CREATE_AUDIO_BUFFER";
	}

	if (DEBUG) std::cout << "OK: create audio buffer" << std::endl;

	//alBufferData(buffer, )
}

void audio::buffer::Delete(unsigned int id)
{

}

void audio::buffer::DeleteALL()
{

}