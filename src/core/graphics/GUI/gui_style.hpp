#include "../../util/structs.hpp"
#include <string>

struct GUIstyle
{
	position_2f pos = position_2f(0, 0);
	size_2f size = size_2f(0, 0);
	color_rgba background = color_rgba(0, 0, 0, 0);
	color_rgba activeBackground = color_rgba(0, 0, 0, 0);

	bool hover = false;
	color_rgba hoverBackground = color_rgba(0, 0, 0, 0);

	std::string text = "";
};