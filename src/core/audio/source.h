#include "audio.h"
#include <glm/glm.hpp>

class audio::Source
{
private:
	glm::vec3 pos;
	glm::vec3 direct;

	unsigned int id;

	const float Pitch = 1.f;
	const float Gain = 1.f;
	const bool LoopSound = false;
	unsigned int Buffer = 0;

public:
	Source(glm::vec3 pos, glm::vec3 direct);
	~Source();

	void Play(const unsigned int audioBuffer);
};