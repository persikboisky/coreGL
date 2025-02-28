#include "core/core.h"
#include "Player.h"
#include <vector>
#include <array>
#include <algorithm> 

double mouseX, mouseY;
bool key[7];
bool cursor = false;
int tic = 0;

float v_r = -0.25f;
float v_g = 0.0f;
float v_b = 0.0f;

float r = 1.0f;
float g = 1.0f;
float b = 1.0f;

int main()
{

	try
	{

		core::Init();
		//create window
		Window window("openGL", 1280, 720);
		window.setContext();

		VAO* submarine = new VAO(vao::FileOBJtoVVO("./res/obj/submarine.obj", true, false));
		submarine->addAttribute(0, 3, 6, 0);
		submarine->addAttribute(1, 3, 6, 3);

		VAO* dragonHead = new VAO(vao::FileOBJtoVVO("./res/obj/dragon_head.obj", true, false));
		dragonHead->addAttribute(0, 3, 6, 0);
		dragonHead->addAttribute(1, 3, 6, 3);

		VAO* Ball = new VAO(vao::FileOBJtoVVO("./res/obj/ball.obj", true, false));
		Ball->addAttribute(0, 3, 6, 0);
		Ball->addAttribute(1, 3, 6, 3);

		unsigned int shader = shader::createFromFile("./res/shaders/mainv.glsl", "./res/shaders/mainf.glsl");

		//creat player
		Player persikboisky(0, 0, 4, 70);

		glEnable(GL_DEPTH_TEST);

		//game Circle
		while (!window.event->close())
		{
			window.event->update();
			if (window.event->getKey(K_ESCAPE))
			{
				window.close();
			}

			if (!cursor)
			{
				window.cursor->getCordCursor(mouseX, mouseY);
				window.cursor->setPosition(0, 0);
			}
			window.cursor->disableCursor(!cursor);

			key[0] = window.event->getKey(K_W);
			key[1] = window.event->getKey(K_S);
			key[2] = window.event->getKey(K_A);
			key[3] = window.event->getKey(K_D);
			key[6] = window.event->getKey(K_SPACE);
			key[4] = window.event->getKey(K_LEFT_SHIFT);
			key[5] = window.event->getKey(K_LEFT_CONTROL);

			if (window.event->getKey(K_ESCAPE))
			{
				window.close();
			}
			if (window.event->getKey(K_F1) && tic > 75)
			{
				tic = 0;
				cursor = !cursor;
			}
			tic += 1;
			if (tic >= 10000000) tic = 100;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 0);

			shader::use(shader);

			persikboisky.move(key);
			persikboisky.render("view", "proj", window.width, window.height, mouseX, mouseY);

			shader::Uniform3F(glm::vec3(0, 0, -2), "u_position");
			shader::Uniform4F(glm::vec4(1, 0.8, 0.03, 1), "u_color");
			submarine->draw(TRIANGLE_STRIP, 0, 93660);

			shader::Uniform3F(glm::vec3(0, -2, -2), "u_position");
			shader::Uniform4F(glm::vec4(1, 0.8, 0.03, 1), "u_color");
			dragonHead->draw(TRIANGLE_STRIP, 0, 1018944);

			shader::Uniform3F(glm::vec3(0, -2, 2), "u_position");
			shader::Uniform4F(glm::vec4(1, 0.8, 0.03, 1), "u_color");
			Ball->draw(TRIANGLE_STRIP, 0, 1018944);

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