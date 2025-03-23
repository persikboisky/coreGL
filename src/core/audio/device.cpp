#include "Device.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

extern bool coreInfo;

audio::Device::Device()
{
	this->alc_device = alcOpenDevice(nullptr);
	
	if (!this->alc_device)
	{
		std::cerr << "Failed: create audio device" << std::endl;
		throw "FAILED_CREATE_AUDIO_DEVICE";
	}

	this->alc_context = alcCreateContext(this->alc_device, nullptr);

	if (!this->alc_context)
	{
		std::cerr << "Failed: create audio context" << std::endl;
		throw "FAILED_CREATE_AUDIO_CONTEXT";
	}

	this->setContext();

	const char* name = NULL;
	if (alcIsExtensionPresent(this->alc_device, "ALC_ENUMERATE_ALL_EXT"))
	{
		name = alcGetString(this->alc_device, ALC_ALL_DEVICES_SPECIFIER);
	}
	if (!name || alcGetError(this->alc_device) != ALC_NO_ERROR)
	{
		name = alcGetString(this->alc_device, ALC_DEVICE_SPECIFIER);
	}
	if (coreInfo) std::cout << "Opened:" << name << std::endl;
}

audio::Device::~Device()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(this->alc_context);
	alcCloseDevice(this->alc_device);
}

void audio::Device::setContext()
{
	if (!alcMakeContextCurrent(this->alc_context))
	{
		std::cerr << "Failed: make audio context" << std::endl;
		throw "FAILED_MAKE_AUDIO_CONTEXT";
	}
}

void audio::Device::setPosition(glm::vec3 pos)
{
	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	//AL_CheckAndThrow();
}

void audio::Device::setPosition(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
}

void audio::Device::setDirect(float atx, float aty, float atz, float upx, float upy, float upz)
{
	std::vector<float> direct;

	direct.push_back(atx);
	direct.push_back(aty);
	direct.push_back(atz);
	direct.push_back(upx);
	direct.push_back(upy);
	direct.push_back(upz);

	alListenerfv(AL_ORIENTATION, direct.data());
}

void audio::Device::getPosition(glm::vec3& pos) const
{
	pos = this->pos;
}

void audio::Device::getPosition(float& x, float& y, float& z) const
{
	x = this->pos.x;
	y = this->pos.y;
	z = this->pos.z;
}
