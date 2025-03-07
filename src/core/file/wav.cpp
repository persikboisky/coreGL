#define DEBUG false

#include "wav.h"
#include "text.h"
#include <AL/al.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

static bool check(const std::string str1, const std::string str2)
{
	for (unsigned int index = 0; index < str1.length() && str1.length() <= str2.length(); index++)
	{
		if (str1[index] != str2[index])
		{
			return false;
		}
	}
	return true;
}

static void loadWav(const char* path, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size)
{
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Failed: open file " << path << std::endl;
		throw "FAILED_OPEN_WAV_FILE";
	}
	if (DEBUG) std::cout << "Ok: open file" << path << std::endl;

	char symbolBuffer[4];
	//---------------------------------------------------------------------------------------------
	//проверка ChunkID 
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 0
	if (!check("RIFF", symbolBuffer))
	{
		std::cerr << "Error: chunkId isn't RIFF" << std::endl;
		throw "ERROR_CHUNKID_ISN'T_RIFF";
	}
	if (DEBUG) std::cout << "Ok: chunkId is RIFF" << std::endl;

	//ChunkSize
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 4
	std::cout << symbolBuffer[0] << symbolBuffer[1] << std::endl;

	//проверка формата
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 8
	if (!check("WAVE", symbolBuffer))
	{
		std::cerr << "Error: chunkId isn't WAVE" << std::endl;
		throw "ERROR_CHUNKID_ISN'T_WAVE";
	}
	if (DEBUG) std::cout << "Ok: chunkId is WAVE" << std::endl;

	//"fmt " or "data"
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 12
	//---------------------------------------------------------------------------------------------
	//Subchunk1Size
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 16

	//AudioFormat
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 20

	//NumChannels
	if (!file.read(symbolBuffer, 2)) throw "FAILED_READ_WAV_FILE"; // 22

	//SampleRate
	if (!file.read(symbolBuffer, 2)) throw "FAILED_READ_WAV_FILE"; // 24

	//ByteRate
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 28
	//---------------------------------------------------------------------------------------------
	
	// BlockAlign
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 32

	//BitsPerSample
	if (!file.read(symbolBuffer, 2)) throw "FAILED_READ_WAV_FILE"; // 34

	//Subchunk2ID 
	if (!file.read(symbolBuffer, 2)) throw "FAILED_READ_WAV_FILE"; // 36

	//Subchunk2Size
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 40

	//Data 
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; // 44
	//---------------------------------------------------------------------------------------------

	file.close();

	//std::ifstream file(path, std::ios::binary);
	//for (unsigned int i = 0; i < 30; i++)
	//{

	//}
	//file.close();
}

void wav::load()
{
	std::uint8_t channels = 0;
	std::int32_t sampleRate = 0;
	std::uint8_t bitsPerSample = 0;
	ALsizei size = 0;

	loadWav("./res/audio/song_start_film.wav", channels, sampleRate, bitsPerSample, size);
}