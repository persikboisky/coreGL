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

double mouseX, mouseY;
bool key[7];
bool cursor = false;
int tic = 0;

int main()
{

	try
	{

		core::Init();
		//create window
		Window window("openGL", 1280, 720);
		window.setContext();
		window.setIcon("./res/png/cubes.png");

		glEnable(GL_DEPTH_TEST);

		GUI::Body* gui = new GUI::Body();
		gui->createButton(0, 0, 0.1, 0.1, 0);
		gui->endCreate();

		//game Circle
		while (!window.event->close())
		{
			window.event->update();
			if (window.event->getKey(K_ESCAPE))
			{
				window.close();
			}

			/*if (!cursor)
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
			if (tic >= 10000000) tic = 100;*/

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.5, 0.5, 0.5, 0);

			gui->Render();

			window.swapBuffers();
			window.setSizeBuffer(window.width, window.height);
		}
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
}