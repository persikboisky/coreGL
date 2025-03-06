#define WIDTH 20
#define HEIGHT 4
#define LENGTH 20

#include "core/core.h"
#include "Player.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <array>
#include <algorithm> 

double mouseX, mouseY;
bool key[7];
bool cursor = false;
int tic = 0;

glm::vec3 mesh[WIDTH][HEIGHT][LENGTH];
glm::mat4 matrix[WIDTH][HEIGHT][LENGTH];

static void setup()
{
	for (unsigned int z = 0; z < LENGTH; z++)
	{
		for (unsigned int x = 0; x < WIDTH; x++)
		{
			for (unsigned int y = 0; y < HEIGHT; y++)
			{
				mesh[x][y][z] = glm::vec3(x * 0.1, y * 0.2, z * 0.1);
				matrix[x][y][z] = glm::mat4(1.0f);
			}
		}
	}
}

int main()
{

	try
	{

		core::Init();
		//create window
		Window window("openGL", 1280, 720);
		window.setContext();

		VAO* Smoke = new VAO(vao::FileOBJtoVVO("./res/obj/smoke/smoke.obj", true, true), 8);
		Smoke->addAttribute(0, 3, 0);
		Smoke->addAttribute(1, 3, 3);
		Smoke->addAttribute(2, 2, 6);
		 
		Shader* shader_2 = new Shader("./res/shaders/mainv.glsl", "./res/shaders/main2f.glsl");
		Texture* textureSmoke = new Texture("./res/obj/smoke/BTV_1_BaseColor.png");

		//creat player
		Player persikboisky(0, 0, 4, 70);

		glEnable(GL_DEPTH_TEST);
		setup();

		audio::Device* device = new audio::Device();

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
			glClearColor(0.5, 0.5, 0.5, 0);

			shader_2->use();
			textureSmoke->bind();

			persikboisky.move(key);
			persikboisky.render("view", "proj", window.width, window.height, mouseX, mouseY);

			//shader_2->Uniform3F(glm::vec3(0, 0, 0), "u_position");
			//texture::bind(Texture);
			//bongo->draw(TRIANGLE_STRIP);
			shader_2->Uniform4F(glm::vec4(1, 1, 1, 1), "u_color");
			for (unsigned int z = 0; z < WIDTH; z++)
			{
				for (unsigned int x = 0; x < HEIGHT; x++)
				{
					for (unsigned int y = 0; y < LENGTH; y++)
					{
						//matrix[x][y][z] = glm::rotate(matrix[x][y][z], 0.01f, glm::vec3(0, 0, 1));

						shader_2->UniformMat4(matrix[x][y][z], "t_matrix");
						shader_2->Uniform3F(mesh[x][y][z], "u_position");
						Smoke->draw(TRIANGLE_STRIP);
					}
				}
			}

			window.swapBuffers();
			window.setSizeBuffer(window.width, window.height);
		}
		texture::DeleteALL();
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