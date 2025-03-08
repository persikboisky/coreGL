#define DEBUG false

#include "Device.h"
#include <AL/alc.h>
#include <iostream>

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
	if (DEBUG) std::cout << "Opened:" << name << std::endl;
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

