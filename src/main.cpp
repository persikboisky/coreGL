#include "core/core.h"
#include "Player.h"
#include <vector>
#include <array>
#include <algorithm> 

double mouseX, mouseY;
bool key[7];
bool cursor = false;
int tic = 0;

std::vector <float> data{
	1, 2, 3,
	1, 2, 3
};

std::vector <float> new_data{
	0, 1,
	1, 1
};

int main()
{

	std::vector<float> v = vao::addElementToVVO(data, 3, new_data, 2);
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << std::endl;
	}

	try
	{
		//init
		int sizeOfArray = 0;
		float* vert = vao::FileOBJtoVAO("./res/obj/dragon_head1.obj", sizeOfArray, false, false);
		core::Init();

		//create window
		Window window("openGL", 1280, 720);
		window.setContext();

		//create vao and shaderProgramm
		unsigned int VAO = vao::create(vert, sizeOfArray * 4);
		vao::addAttribute(VAO, 0, 3, 3, 0);
		vao::bind(VAO);
		unsigned int shader = shader::createFromFile("./res/shaders/mainv.glsl", "./res/shaders/mainf.glsl");
		
		//creat player
		Player persikboisky(0, 0, 4, 70);

		//game Circle
		while (!window.event->close())
		{
			window.event->update();
			if (window.event->getKey(ESCAPE))
			{
				window.close();
			}

			if (!cursor)
			{
				window.cursor->getCordCursor(mouseX, mouseY);
				window.cursor->setPosition(0, 0);
			}
			window.cursor->disableCursor(!cursor);

			key[0] = window.event->getKey(W);
			key[1] = window.event->getKey(S);
			key[2] = window.event->getKey(A);
			key[3] = window.event->getKey(D);
			key[6] = window.event->getKey(SPACE);
			key[4] = window.event->getKey(LEFT_SHIFT);
			key[5] = window.event->getKey(LEFT_CONTROL);

			if (window.event->getKey(ESCAPE))
			{
				window.close();
			}
			if (window.event->getKey(F1) && tic > 75)
			{
				tic = 0;
				cursor = !cursor;
			}
			tic += 1;
			if (tic >= 10000000) tic = 100;

			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0, 0, 0, 0);

			shader::use(shader);

			persikboisky.move(key);
			persikboisky.render("view", "proj", window.width, window.height, mouseX, mouseY);

			shader::Uniform4F(glm::vec4(1, 1, 1, 1), "color");
			shader::Uniform3F(glm::vec3(0, 0, 2), "position");
				
			vao::draw(TRIANGLE_STRIP, 0, 350000);

			window.swapBuffers();
			window.setSizeBuffer(window.width, window.height);
		}
		vao::DeleteALL();
		shader::DeleteALL();
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
};