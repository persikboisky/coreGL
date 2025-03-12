#include <glm/glm.hpp>
#include <string>

namespace GUI
{
	class Style
	{
	public:
		//void load(const char* path);
		glm::vec4 background;
		glm::vec4 color;
		std::string text;
		bool flag;
	};
}