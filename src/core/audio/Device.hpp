#pragma Device

#include "audio.hpp"
#include <glm/glm.hpp>

struct ALCdevice;
struct ALCcontext;

class audio::Device
{
private:
	ALCdevice* alc_device;
	ALCcontext* alc_context;

	glm::vec3 pos = glm::vec3(0, 0, 0);

public:
	Device();
	~Device();

	void setContext();

	void setPosition(glm::vec3 pos);
	void setPosition(float x, float y, float z);

	void setDirect(float atx, float aty, float atz, float upx, float upy, float upz);

	void getPosition(glm::vec3& pos) const;
	void getPosition(float& x, float& y, float& z) const;
};
