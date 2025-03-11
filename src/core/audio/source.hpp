#include "audio.hpp"
#include <glm/glm.hpp>
#include <vector>

typedef int ALint;

struct audio::source
{
private:
	static std::vector<unsigned int> id;

public:
	static unsigned int create(glm::vec3 pos, glm::vec3 direct);
	static unsigned int create(float pos_x, float pos_y, float pos_z, float direct_x, float direct_y, float dirct_z);

	static void linkBuffer(unsigned int source, unsigned int audioBuffer);

	static void setSpeed(unsigned int source, float value);
	static void setVolume(unsigned int source, float value);

	static void play(unsigned int source);
	static void stop(unsigned int source);
	static void pause(unsigned int source);
	static void Resume(unsigned int source);

	static void GetSourceState(unsigned int source, ALint& state);
	static bool isPlaying(unsigned int source);

	static void Delete(unsigned int source);
	static void DeleteALL();
};

//class audio::Source
//{
//private:
//	glm::vec3 pos;
//	glm::vec3 direct;
//
//	unsigned int id_source;
//
//public:
//	Source(glm::vec3 pos, glm::vec3 direct);
//	Source(float pos_x, float pos_y, float pos_z, float direct_x, float direct_y, float direct_z);
//	~Source();
//
//	void linkBuffer(unsigned int audioBuffer);
//	//void GetSourceState(ALint& state);
//};