#include "core/core.h"
#include "Player.h"
#include <vector>

double mouseX, mouseY;
bool key[7];
bool cursor = false;
int tic = 0;

int main()
{
	try
	{
		std::vector<float> OBJ = vao::loadFromOBJ("./res/obj/five_number.obj");
		core::Init();

		Window window("openGL", 1280, 720);
		window.setContext();

		unsigned int VAO = vao::create(OBJ);
		vao::addAttribute(VAO, 0, 3, 3, 0);
		unsigned int shader = shader::createFromFile("./res/shaders/mainv.glsl", "./res/shaders/mainf.glsl");
		
		Player persikboisky(0, 0, 4, 70);

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

			vao::draw(TRIANGLE_STRIP, VAO, 0, 180);

			window.swapBuffers();
			window.setSizeBuffer(window.width, window.height);
		}

		vao::DeleteAll();


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
}
