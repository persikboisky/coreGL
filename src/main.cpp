#include "core/core.h"
#include "Player.h"
#include <vector>

//std::vector<float> v;
//std::vector<int> f;
//std::vector<float> triangle {
//   -1.258860, 2.432199, 1.572720,
//   -1.258860, -2.432199, -1.572720,
//   -1.258860, -2.432199, 1.572720,
//
//	-1.258860, 2.432199, -1.572720,
//	1.258860, -2.432199, -1.572720,
//	-1.258860, -2.432199, -1.572720,
//
//	1.258860, 2.432199, -1.572720,
//	1.258860, -2.432199, 1.572720,
//	1.258860, -2.432199, -1.572720
//};

double mouseX, mouseY;
bool key[7];
bool cursor = false;
int tic = 0;

float cord[5] = { 0, 0, 0, 0, 0 };
float Cord[5] = { 2, 2, 2, 2, 2 };
float velocity = 0.01;
float Velocity = -0.01;

int main()
{
	std::vector<float> VVO = vao::loadFromOBJ("./res/circle.obj");
	core::Init();

	{
		Window window("openGL", 1280, 720);
		window.setIcon("./res/cubes.png");
		window.setContext();

		unsigned int shader = shader::createFromFile("./res/vertex.glsl", "./res/fragment.glsl");
		unsigned int vao = vao::create(VVO);
		vao::addAttribute(vao, 0, 3, 3, 0);

		Player persikboisky(6, 4, 7, 70);

		while (!window.event->close())
		{
			window.event->update();
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
			//std::cout << tic << std::endl;
			tic += 1;
			if (tic >= 10000000) tic = 100;

			window.setSizeBuffer(window.width, window.height);
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0, 0, 0, 1);

			shader::use(shader);
			persikboisky.move(key);
			persikboisky.render("view", "proj", window.width, window.height, mouseX, mouseY);

			for (int i = 0; i < 5; i++)
			{
				cord[i] += velocity;
				if (cord[i] >= 4 || cord[i] <= -2) velocity = -velocity;
			}

			for (int i = 0; i < 5; i++)
			{
				Cord[i] += Velocity;
				if (Cord[i] >= 4 || Cord[i] <= -2) Velocity = -Velocity;
			}

			shader::Uniform3F(glm::vec3(0, cord[0], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(0, Cord[0], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(3, cord[1], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(3, Cord[1], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(6, cord[2], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(6, Cord[2], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(9, cord[3], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(9, Cord[3], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(12, cord[4], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			shader::Uniform3F(glm::vec3(12, Cord[4], 0), "cord");
			shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			vao::draw(TRIANGLE_STRIP, vao, 0, 2880);

			//shader::Uniform3F(glm::vec3(1, 1, 1), "color");
			//vao::draw(LINE_STRIP, vao, 0, 960);
			window.swapBuffers();
		}

		vao::DeleteALL();
		shader::DeleteALL();
	}

	core::Terminate();
	return 0;
}
