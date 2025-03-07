#include "source.h"
#include <AL/alext.h>
#include <glm/glm.hpp>
#include <iostream>

audio::Source::Source(glm::vec3 pos, glm::vec3 direct) : pos(pos), direct(direct)
{
	alGenSources(1, &this->id);
	if (this->id == 0)
	{
		std::cerr << "Failed: create audio source" << std::endl;
		throw "FAILED_CREATE_AUDIO_SOURCE";
	}

	alSourcef(this->id, AL_PITCH, this->Pitch);
	alSourcef(this->id, AL_GAIN, this->Gain);
	alSource3f(this->id, AL_POSITION, this->pos.x, this->pos.y, this->pos.z);
	alSource3f(this->id, AL_VELOCITY, this->direct.x, this->direct.y, this->direct.z);
	alSourcei(this->id, AL_LOOPING, this->LoopSound);
	alSourcei(this->id, AL_BUFFER, this->Buffer);
}

audio::Source::~Source()
{
	alDeleteSources(1, &this->id);
}

void audio::Source::Play(const unsigned int audioBuffer)
{
	if (audioBuffer == this->Buffer)
	{
		std::cerr << "Failed: play audio buffer" << std::endl;
		throw "FAILED_PLAY_AUDIO_BUFFER";
	}

	this->Buffer = audioBuffer;

	alSourcePlay(this->id);

	ALint state = AL_PLAYING;
	//std::cout << "playing sound\n";
	while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		//std::cout << "currently playing sound\n";
		alGetSourcei(this->id, AL_SOURCE_STATE, &state);
	}
	//std::cout << "done playing sound\n";
}

