#include "core/core.h"

float vert[] = { 
	-1, 1, 0, 0, 0,
	-1,-1, 0, 0, 1,
	 1,-1, 0, 1, 1,
	-1, 1, 0, 0, 0,
	 1,-1, 0, 1, 1,
	 1, 1, 0, 1, 0
};

int main()
{
	std::cout << toml::searchString("WIDTH", "./res/config.toml") << std::endl;

	try
	{
		core::Init();
		Window* window = new Window("openGL", 1280, 720);
		window->setIcon("./res/cubes.png");
		window->setContext();

		unsigned int text = texture::load("./res/cubes.png");

		unsigned int shaderID = shader::createFromFile("./res/main.vert", "./res/main.frag");
		unsigned int VAO = vao::create(vert, sizeof(vert));
		vao::addAttribute(VAO, 0, 3, 5, 0);
		vao::addAttribute(VAO, 1, 2, 5, 3);

		Camera* cam = new Camera(0, 0, 4, 70);

		while (!window->event->close())
		{

			glClearColor(0.6f, 0.62f, 0.65f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//cam->rotate(0, 0, 0.01);

			shader::use(shaderID);
			texture::bind(text);

			shader::setValueUniform(cam->getProj(window->width, window->height), "project");
			shader::setValueUniform(cam->getView(), "view");
			
			vao::draw(TRIANGLE, VAO, 0, 6);

			window->event->update();
			window->swapBuffers();
			window->setSizeBuffer(window->width, window->height);

			if (window->event->getKey(256)) window->close();
			//std::cout << window->height << std::endl;
		}

		texture::DeleteALL();
		vao::DeleteAll();
		shader::Delete(shaderID);
	}
	catch (...)
	{
		return -1;
	}

	glfwTerminate();
	return 0;
}