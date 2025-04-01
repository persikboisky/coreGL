#include <string>
#include "../../data/structs.hpp"

struct gui_style
{
	color_rgba background;
	color_rgba active_background;

	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;

	std::string text = "";

	gui_style() : 
		background(color_rgba(255.0f, 255.0f, 255.0f, 255.0f)),
		active_background(color_rgba(255.0f, 0.0f, 0.0f, 255.0f))
	{ }

	~gui_style()
	{
	}
};