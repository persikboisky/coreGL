#include "GUI.hpp"
//#include "Elements/Button.hpp"
//#include "Elements/Text.hpp"
#include "../../window/Window.hpp"
#include "../commons/shader.hpp"
#include "../commons/font.hpp"

// путь к шейдерам для интерфейса
constexpr const char* PATH_TO_VERTEX_SHADER = "./res/gui/main_gui_v.glsl";
constexpr const char* PATH_TO_FRAGMENT_SHADER = "./res/gui/main_gui_f.glsl";

unsigned int GUI::ShaderID = 0;

GUI::GUI(Window& window, font& objFont) : 
	addrWindow(&window), objFont(&objFont), button(new Button())//, text(new Text())
{
	if (GUI::ShaderID == 0)
	{
		GUI::ShaderID = shader::createFromFile(
			PATH_TO_VERTEX_SHADER,
			PATH_TO_FRAGMENT_SHADER
		);
	}
}

GUI::~GUI()
{
	delete this->button;
}

void GUI::render()
{
	bool leftButtonMouse = this->addrWindow->event->GetMouseLeftButton();

	double MouseX, MouseY;
	this->addrWindow->cursor->getCordCursor(MouseX, MouseY);
	MouseX = MouseX / double(addrWindow->width / 2.0) - 1.0;
	MouseY = -(MouseY / double(addrWindow->height / 2.0) - 1.0);

	shader::use(GUI::ShaderID);
	this->button->update(MouseX, MouseY, leftButtonMouse);
	this->button->render(/*fonts*/);
}