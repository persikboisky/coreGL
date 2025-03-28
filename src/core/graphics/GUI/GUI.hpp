#include <vector>
#include <glm/vec2.hpp>

enum GUI_ELEMENTS
{
	BUTTON
};

struct gui_style;
class VAO;
class Shader;
class Window;

class GUI
{
private:
	unsigned int n_Elements;

	std::vector<gui_style> style;
	std::vector<GUI_ELEMENTS> elements;
	std::vector<void(*)()> function;

	void compileVAO();
	bool compileFlag = true;

	VAO* vao;
	Shader* shader;
	Window* window;

public:
	GUI(Window* window);
	~GUI();

	void addButton(
		gui_style* style,
		void(*function)() = nullptr
	);

	void setWindow(Window* window);
	void render();
};