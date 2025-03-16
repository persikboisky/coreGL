//#define WIDTH 20
//#define HEIGHT 4
//#define LENGTH 20

#include "core/core.h"
#include "Player.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <array>
#include <algorithm> 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <math.h>

#include <ctime>
#include <chrono>

std::vector<float> vertex;

int main()
{

	try
	{
		core::Init();
		//create window
		Window window("openGL", 1280, 720);
		window.setContext();
		window.setIcon("./res/png/cubes.png");

		for (float a = -15; a < 15; a += 0.001)
		{
			vertex.push_back(a / 10);
			vertex.push_back(cos(a) / 2);
		}

		VAO* vao = new VAO(vertex, 2);
		vao->addAttribute(0, 2, 0);
		vao->addAttribute(1, 2, 0);

		Shader* shader = new Shader("./src/vert.glsl", "./src/frag.glsl");
		Texture* texture = new Texture("./res/png/cubes.png");

		glEnable(GL_DEPTH_TEST);

		//game Circle
		while (!window.event->close())
		{
			window.event->update();
			if (window.event->getKey(K_ESCAPE))
			{
				window.close();
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glClearColor(0.5, 0.5, 0.5, 0);
			glClearColor(0, 0, 0, 0);

			//texture->bind();
			shader->use();
			//shader->Uniform3F(glm::vec3(1, 1, 1), "color");
			//shader->Uniform1I(glm::ivec1(2), "text");
			glPointSize(2);
			vao->draw(POINT);

			window.swapBuffers();
			window.setSizeBuffer(window.width, window.height);
		}
		shader::DeleteALL();
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
}