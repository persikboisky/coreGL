#include "Elements/Button.hpp"

//font;

class Window;

class GUI
{
private:
	Window* addrWindow;

	static unsigned int ShaderID;

	//font* fonts;

public:
	GUI(Window& window);
	~GUI();

	Button* button = nullptr;

	void render();
};