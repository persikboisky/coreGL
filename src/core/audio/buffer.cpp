#define DEBUG true

#include "buffer.hpp"
#include "../file/wav.hpp"
#include "../util/vector.hpp"
#include <AL/alext.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> audio::buffer::id;

unsigned int audio::buffer::create(const char* path)
{
	ALuint buffer;
	ALenum format;

	alGenBuffers(1, &buffer);

	bool flag = true;
	int index = vector::searchElemntForValue(id, 0);
	if (index != -1 && buffer != 0)
	{
		id[index] = buffer;
		flag = false;
	}

	if (flag)
	{
		if (buffer != 0)
		{
			buffer::id.push_back(buffer);
		}
		else
		{
			std::cerr << "Failed create audio buffer" << "\n";
			throw "FAILED_CREATE_AUDIO_BUFFER";
		}
	}

	std::uint8_t channels;
	std::int32_t sampleRate;
	std::uint8_t bitsPerSample; 
	ALsizei size;

	std::vector<char> dataAudio = wav::load(path, channels, sampleRate, bitsPerSample, size);

	int chan = int(channels);
	int BPS = int(bitsPerSample);

	std::int_fast32_t numberOfSamples = dataAudio.size() / (channels * (bitsPerSample / 8));
	std::size_t duration = numberOfSamples / sampleRate;

	if (chan == 1 && BPS == 8)
		format = AL_FORMAT_MONO8;
	else if (chan == 1 && BPS == 16)
		format = AL_FORMAT_MONO16;
	else if (chan == 2 && BPS == 8)
		format = AL_FORMAT_STEREO8;
	else if (chan == 2 && BPS == 16)
		format = AL_FORMAT_STEREO16;
	else
	{
		std::cerr
			<< "ERROR: unrecognised wave format: "
			<< channels << " channels, "
			<< bitsPerSample << " bps" << std::endl;
		throw "FAILED_DEFINITION_FORMAT";
	}

	alBufferData(buffer, format, dataAudio.data(), dataAudio.size(), sampleRate);

	dataAudio.clear();

	if (DEBUG) std::cout << "OK: create audio buffer: " << path << std::endl;

	return buffer;
}

void audio::buffer::Delete(unsigned int buffer)
{
	if (buffer < id.size())
	{
		id[vector::searchElemntForValue(id, buffer)] = 0;
		alDeleteBuffers(1, &buffer);
	}
}

void audio::buffer::DeleteALL()
{
	for (int i = 0; i < id.size(); i++)
	{
		alDeleteBuffers(1, &id[i]);
		id.clear();
	}
}