#define BUILD false

#include "source.hpp"
#include "../util/vector.hpp"
#include <AL/alext.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

std::vector<unsigned int> audio::source::id;

unsigned int audio::source::create(glm::vec3 pos, glm::vec3 direct)
{
	ALuint source;
	alGenSources(1, &source);

	bool flag = true;
	int index = vector::searchElemntForValue(id, 0);
	if (index != -1 && source != 0)
	{
		id[index] = source;
		flag = false;
	}

	if (flag)
	{
		if (source != 0)
		{
			id.push_back(source);
		}
		else
		{
			std::cerr << "Failed create Texture" << "\n";
			throw "FAILED_CREATE_VAO";
		}
	}

	if (BUILD) std::cout << "OK: create audio source, id = " << source << std::endl;

	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
	alSource3f(source, AL_VELOCITY, direct.x, direct.y, direct.z);
	alSourcei(source, AL_LOOPING, AL_FALSE);
}

unsigned int audio::source::create(float pos_x, float pos_y, float pos_z, float direct_x, float direct_y, float direct_z)
{
	return create(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(direct_x, direct_y, direct_z));
}

void audio::source::linkBuffer(unsigned int source, unsigned int audioBuffer)
{
	alSourcei(source, AL_BUFFER, audioBuffer);
}

void audio::source::setSpeed(unsigned int source, float value = 1.0f)
{
	alSourcef(source, AL_PITCH, value);
}

void audio::source::setVolume(unsigned int source, float value = 1.0f)
{
	if (value < 0.0f) value = 0.0f;
	else if (value > 5.0f) value = 5.0f;
	alSourcef(source, AL_GAIN, value);
}

void audio::source::play(unsigned int source)
{
	alSourcePlay(source);
}

void audio::source::stop(unsigned int source)
{
	alSourceStop(source);
}

void audio::source::pause(unsigned int source)
{
	alSourcePause(source);
}

void audio::source::Resume(unsigned int source)
{
	alSourcePlay(source);
}

void audio::source::GetSourceState(unsigned int source, ALint& state)
{
	alGetSourcei(source, AL_SOURCE_STATE, &state);
}

bool audio::source::isPlaying(unsigned int source)
{
	ALint playState;
	GetSourceState(source, playState);
	return (playState == AL_PLAYING);
}

void audio::source::Delete(unsigned int source)
{
	if (source < id.size())
	{
		id[vector::searchElemntForValue(id, source)] = 0;
		alDeleteSources(1, &source);
	}
}

void audio::source::DeleteALL()
{
	for (int i = 0; i < id.size(); i++)
	{
		alDeleteSources(1, &id[i]);
		id.clear();
	}
}

//audio::Source::Source(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 direct = glm::vec3(0, 0, 0)) : pos(pos), direct(direct)
//{
//	this->id_source = audio::source::create(this->pos, this->direct);
//}

//audio::Source::Source(float pos_x = 0, float pos_y = 0, float pos_z = 0, float direct_x = 0, float direct_y = 0, float direct_z = 0):
//	pos(pos_x, pos_y, pos_z), direct(direct_x, direct_y, direct_z)
//{
//	this->id_source = create(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(direct_x, direct_y, direct_z));
//}
//
//audio::Source::~Source()
//{
//	Delete(this->id_source);
//}

//void audio::Source::linkBuffer(unsigned int audioBuffer)
//{
//	alSourcei(this->id_source, AL_BUFFER, audioBuffer);
//}