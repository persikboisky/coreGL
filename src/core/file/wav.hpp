#pragma Wav

#include <string>
#include <vector>

typedef int ALsizei;

namespace wav
{
	std::vector<char> load(const char* path, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size);
}
