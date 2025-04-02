#define DEBUG false

#include "wav.hpp"
#include "text.hpp"
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

static std::vector<char> readWav(const char* path, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size)
{
	unsigned int infoByte = 0;

	std::ifstream file(path, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Failed: open file " << path << std::endl;
		throw "FAILED_OPEN_WAV_FILE";
	}
	if (DEBUG) std::cout << "Ok: open file" << path << std::endl;

	char symbolBuffer[4];
	//---------------------------------------------------------------------------------------------
	//проверка ChunkID (4)
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE";
	if (!check("RIFF", symbolBuffer))
	{
		std::cerr << "Error: chunkId isn't RIFF" << std::endl;
		throw "ERROR_CHUNKID_ISN'T_RIFF";
	}
	if (DEBUG) std::cout << "Ok: chunkId is RIFF" << std::endl;
	infoByte += 4;

	//ChunkSize(4)
	int ChunkSize = 0;
	if (!file.read((char*)&ChunkSize, 4)) throw "FAILED_READ_WAV_FILE";
	infoByte += 4;

	//проверка формата(4)
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; 
	if (!check("WAVE", symbolBuffer))
	{
		std::cerr << "Error: chunkId isn't WAVE" << std::endl;
		throw "ERROR_CHUNKID_ISN'T_WAVE";
	}
	if (DEBUG) std::cout << "Ok: chunkId is WAVE" << std::endl;
	infoByte += 4;
	//---------------------------------------------------------------------------------------------

	//"fmt "(4)
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; 
	//check
	if (symbolBuffer[0] != 'f' || symbolBuffer[1] != 'm' || symbolBuffer[2] != 't')
	{
		std::cerr << "Error: format wav file isn't fmt" << std::endl;
		throw "ERROR_FORMAT_WAV_FILE_ISN'T_FMT";
	}
	infoByte += 4;

	//Subchunk1Size(4)
	int Subchunk1Size = 0;
	if (!file.read((char*)&Subchunk1Size, 4)) throw "FAILED_READ_WAV_FILE";
	infoByte += 4;

	//AudioFormat (PCM)
	int AudioFormat = 0;
	if (!file.read((char*)&AudioFormat, 2)) throw "FAILED_READ_WAV_FILE"; 
	if (AudioFormat != 1)
	{
		std::cerr << "ERROR: wav file hasn't pcm format" << std::endl;
		throw "ERROR_WAV_FILE_HASN'T_PCM_FORMAT";
	}
	infoByte += 2;

	//NumChannels
	if (!file.read((char*)&channels, 2)) throw "FAILED_READ_WAV_FILE";
	infoByte += 2;

	//SampleRate(4)
	if (!file.read((char*)&sampleRate, 4)) throw "FAILED_READ_WAV_FILE";
	infoByte += 4;

	//ByteRate(4)
	if (!file.read(symbolBuffer, 4)) throw "FAILED_READ_WAV_FILE"; 
	infoByte += 4;
	
	// BlockAlign(2)
	if (!file.read(symbolBuffer, 2)) throw "FAILED_READ_WAV_FILE"; 
	infoByte += 2;

	//BitsPerSample
	if (!file.read((char*)&bitsPerSample, 2)) throw "FAILED_READ_WAV_FILE";
	infoByte += 2;

	//---------------------------------------------------------------------------------------------

	//SubchunkDATA
	for (unsigned int byte = 0;; byte += 1)
	{
		infoByte += 2;
		if (!file.read(symbolBuffer, 2)) throw "FAILED_READ_WAV_FILE";
		if (symbolBuffer[0] != 'd' || symbolBuffer[1] != 'a') continue;

		char symbolBuffer_2[2];
		if (!file.read(symbolBuffer_2, 2)) throw "FAILED_READ_WAV_FILE";
		if (!check("ta", symbolBuffer_2)) throw "FAILED_READ_WAV_FILE";

		infoByte += 2;
		break;
	}

	//Subchunk2Size
	int Subchunk2Size;
	if (!file.read((char*)&Subchunk2Size, 4)) throw "FAILED_READ_WAV_FILE";
	size = Subchunk2Size;
	infoByte += 4;

	//samples

	std::vector<char> data;
	data.resize(size);

	if (!file.read(data.data(), size)) throw "FAILED_READ_WAV_FILE";

	//std::cout << ChunkSize << " : " << ChunkSize - Subchunk2Size << " : " << Subchunk2Size << std::endl;

	//---------------------------------------------------------------------------------------------

	file.close(); 
	return data;
}

std::vector<char> wav::load(const char* path, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size)
{
	std::vector<char> data = readWav(path, channels, sampleRate, bitsPerSample, size);

	if (DEBUG)
	{
		std::cout << "\nINFO WAV FILE: \n" << "Path: " << path << std::endl;
		std::cout << "Channels: " << int(channels) << "\nSampleRate: " << sampleRate << std::endl;
		std::cout << "bitsPerSample: " << int(bitsPerSample) << "\nsize: " << size << std::endl;
	}

	return data;
}