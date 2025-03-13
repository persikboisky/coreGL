#include <glm/glm.hpp>
#include <string>

enum Element;

namespace GUI
{
	class Style
	{
	public:
		//void load(const char* path);
		Element index_element;

		glm::vec4 background;
		glm::vec4 color;

		std::string text;

		bool flag;
	};
}