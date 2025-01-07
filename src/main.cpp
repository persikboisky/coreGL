#include "engineSoft/engine.hpp"

unsigned int WIDTH = json::getValueFromJSON("./res/config.json", "WIDTH");
unsigned int HEIGHT = json::getValueFromJSON("./res/config.json", "HEIGHT");

float vertex[] = {
	  -1, 1, 0, 0, 0,
	  -1,-1, 0, 0, 0,
	   1,-1, 0, 0, 0,
	  -1, 1, 0, 0, 0,
	   1,-1, 0, 0, 0,
	   1, 1, 0, 0, 0,

	   0,  0.5, 1, 1, 1,
	-0.5, -0.5, 1, 1, 1,
	 0.5, -0.5, 1, 1, 1
};

unsigned int VAO;
unsigned int Shader;

int main() 
{
	try 
	{
		window::create("openGL", WIDTH, HEIGHT);
		window::setIcon("./res/icon.png");
		event::init();

		VAO = vao::create(vertex, sizeof(vertex));
		vao::addAttribute(VAO, 0, 2, 5, 0);
		vao::addAttribute(VAO, 1, 3, 5, 2);

		Shader = shader::create("./res/main.vert", "./res/main.frag");
	}
	catch (...)
	{
		return -1;
	}

	Camera cam(0, 0, 1, 70);

	while (!event::closeWindow())
	{
		event::update();

		cam.rotate(0, 0, 0.01);

		shader::use(Shader);
		shader::setValueUniform(cam.getProj(), "project");
		shader::setValueUniform(cam.getView(), "view");
		vao::draw(TRIANGLE, VAO, 0, 9);
		window::swapBuffers();
	}

	window::destroy();
	return 0;
}