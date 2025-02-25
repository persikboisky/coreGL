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
		std::vector<float> vert1 = vao::FileOBJtoVVO("./res/obj/cube.obj", true, false);
		std::vector<float> v_color;

		//std::cout << vert1.size() << std::endl;
		int put = 0;
		for (unsigned int i = 0; i < vert1.size() / 3; i++)
		{
			v_color.push_back(r); // r
			v_color.push_back(1); // g
			v_color.push_back(1); // b
			v_color.push_back(1); // a

			r += v_r;
			g += v_g;
			b += v_b;

			if (r <= 0 || r >= 1) v_r = -v_r;
		}
		std::vector<float> vert = vao::addElementToVVO(vert1, 6, v_color, 4);

		core::Init();
		//create window
		Window window("openGL", 1280, 720);
		window.setContext();

		//create vao and shaderProgramm
		unsigned int VAO = vao::create(vert);
		vao::addAttribute(VAO, 0, 3, 10, 0);
		vao::addAttribute(VAO, 1, 3, 10, 3);
		vao::addAttribute(VAO, 2, 4, 10, 6);
		vao::bind(VAO);
		unsigned int shader = shader::createFromFile("./res/shaders/mainv.glsl", "./res/shaders/mainf.glsl");
		
		//creat player
		Player persikboisky(0, 0, 4, 70);

		glEnable(GL_DEPTH_TEST);

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

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 0);

			shader::use(shader);

			persikboisky.move(key);
			persikboisky.render("view", "proj", window.width, window.height, mouseX, mouseY);

			shader::Uniform3F(glm::vec3(0, 0, -2), "position");
				
			vao::draw(TRIANGLE_STRIP, 0, 36/*350000*/);

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