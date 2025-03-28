struct s_color
{
	float red = 255.0f;
	float green = 255.0f;
	float blue = 255.0f;
	float alhpa = 255.0f;
};

struct gui_style
{
	s_color background;
	s_color active_background;

	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;

	gui_style()
	{
		active_background.green = 255.0f;
		active_background.red = 0.0f;
		active_background.blue = 0.0f;
		active_background.alhpa = 255.0f;
	}

	~gui_style()
	{
	}
};