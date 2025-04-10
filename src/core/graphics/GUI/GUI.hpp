#include "Elements/Button.hpp"
//#include "Elements/Text.hpp"

class Window;
struct font;

class GUI
{
private:
	Window* addrWindow;
	font* objFont;

	static unsigned int ShaderID;

public:
	GUI(Window& window, font& objFont);
	~GUI();

	Button* button = nullptr;
	//Text* text = nullptr;

	void render();
};