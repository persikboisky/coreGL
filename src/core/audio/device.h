#pragma Device

#include "audio.h"

struct ALCdevice;
struct ALCcontext;

class audio::Device
{
private:
	ALCdevice* alc_device;
	ALCcontext* alc_context;

public:
	Device();
	~Device();

	void setContext();
};