#include "core/core.hpp"
#include <math.h>
#include <vector>

static void print()
{
	std::cout << "Hello World" << std::endl;
}

int main()
{
	math::Vector3 vec = math::Vector3(10, 10, 10);
	vec = vec + math::Vector3(1, 1, 1);
	vec = vec - math::Vector3(10, 0, 0);
	std::cout << vec.x << std::endl;

	try
	{
		core::Init();
		Window win("test", 720, 720);
		win.setIcon("cubes.png");
		win.setContext();

		Shader shader("v.glsl", "f.glsl");
		shader.use();

#pragma region CREATE_VAO
		VAO vao({
		   -0.5, 0.5, 0.5, 1.0, 0.0, 1.0,
		   -0.5,-0.5, 0.5, 1.0, 0.0, 0.0,
			0.5,-0.5, 0.5, 1.0, 1.0, 0.0,
		   -0.5, 0.5, 0.5, 1.0, 0.0, 1.0,
			0.5,-0.5, 0.5, 1.0, 1.0, 0.0,
			0.5, 0.5, 0.5, 1.0, 1.0, 1.0,

		   -0.5, 0.5,-0.5, 0.0, 1.0, 0.0,
		   -0.5, 0.5, 0.5, 0.0, 1.0, 0.0,
		    0.5, 0.5, 0.5, 0.0, 1.0, 0.0,
		   -0.5, 0.5,-0.5, 0.0, 1.0, 0.0,
		    0.5, 0.5, 0.5, 0.0, 1.0, 0.0,
			0.5, 0.5,-0.5, 0.0, 1.0, 0.0,

			0.5, 0.5,-0.5, 1.0, 1.0, 1.0,
			0.5,-0.5,-0.5, 1.0, 1.0, 0.0,
		   -0.5,-0.5,-0.5, 1.0, 0.0, 0.0,
		    0.5, 0.5,-0.5, 1.0, 1.0, 1.0,
		   -0.5,-0.5,-0.5, 1.0, 0.0, 0.0,
		   -0.5, 0.5,-0.5, 1.0, 0.0, 1.0,

		   -0.5,-0.5, 0.5, 0.0, 0.0, 1.0,
		   -0.5,-0.5,-0.5, 0.0, 0.0, 1.0,
		    0.5,-0.5,-0.5, 0.0, 0.0, 1.0,
		   -0.5,-0.5, 0.5, 0.0, 0.0, 1.0,
			0.5,-0.5,-0.5, 0.0, 0.0, 1.0,
			0.5,-0.5, 0.5, 0.0, 0.0, 1.0,

			0.5, 0.5, 0.5, 1.0, 0.0, 1.0,
			0.5,-0.5, 0.5, 1.0, 0.0, 1.0,
			0.5,-0.5,-0.5, 1.0, 0.0, 1.0,
			0.5, 0.5, 0.5, 1.0, 0.0, 1.0,
			0.5,-0.5,-0.5, 1.0, 0.0, 1.0,
			0.5, 0.5,-0.5, 1.0, 0.0, 1.0,

		   -0.5, 0.5,-0.5, 1.0, 1.0, 1.0,
		   -0.5,-0.5,-0.5, 1.0, 1.0, 1.0,
		   -0.5,-0.5, 0.5, 1.0, 1.0, 1.0,
		   -0.5, 0.5,-0.5, 1.0, 1.0, 1.0,
		   -0.5,-0.5, 0.5, 1.0, 1.0, 1.0,
		   -0.5, 0.5, 0.5, 1.0, 1.0, 1.0
		}, 6);
		vao.addAttribute(0, 3, 0);
		vao.addAttribute(1, 3, 3);

		VAO triangle({
			-0.5, 0.5, 0.0,   1.0, 1.0, 1.0,   0, 0,
			-0.5,-0.5, 0.0,   1.0, 1.0, 1.0,   0, 1,
			 0.5,-0.5, 0.0,   1.0, 1.0, 1.0,   1, 1,
			-0.5, 0.5, 0.0,   1.0, 1.0, 1.0,   0, 0,
			 0.5,-0.5, 0.0,   1.0, 1.0, 1.0,   1, 1,
			 0.5, 0.5, 0.0,   1.0, 1.0, 1.0,   1, 0
			},8);
		triangle.addAttribute(0, 3, 0);
		triangle.addAttribute(1, 3, 3);
		triangle.addAttribute(2, 2, 6);
#pragma endregion CREATE_VAO

		font Font;

		GUI gui(win, Font);
		GUIstyle style;

		style.pos = position_2f(0, 0);
		style.size = size_2f(0.1, 0.1);
		style.background = color_rgba(255, 0, 0, 255);
		style.activeBackground = color_rgba(0, 255, 0, 255);

		gui.button->add(style, print);

		style.hover = true;
		style.hoverBackground = color_rgba(255, 0, 0, 150);
		style.pos = position_2f(0.2, 0);
		style.text = "Hello World";
		gui.button->add(style, print, "t");

		font classic_font;

		BufferText2D buffer_1;
		buffer_1.linkFont(classic_font);

		//buffer_1.addText("Hello world", 0, 0.5, 0.5, 10.0f);
		//buffer_1.addText("пистолет", -1, 0.1, 0.3);

		buffer_1.addText("Привет ", 0.0, 0.1, 0.5, 25.0f);

		while (!win.event->close())
		{

			win.event->update();
#pragma region RENDER_CUBES
			shader.use();
			float rotate = glm::radians(core::GetTime() * 30);

			glm::vec3 cam_pos = glm::vec3(0.0, 0.0, 6.0);
			glm::vec3 cam_target = glm::vec3(
				sin(core::GetTime()) * 3.0, 
				cos(core::GetTime()) * 3.0, 
				0.0);
			glm::vec3 cam_up = glm::vec3(0, 1, 0);

			glm::mat4 view = glm::lookAt(cam_pos, cam_target, cam_up);
			glm::mat4 proj = glm::perspective(
				glm::radians(70.0f),
				float(win.width) / float(win.height),
				0.01f, 100.0f);

			glm::mat4 matrix = glm::mat4(1.0f);
			//matrix = glm::translate(matrix, glm::vec3(0.0, 0.0, -1.0));
			matrix = glm::rotate(matrix, rotate, glm::vec3(-0.01, 0.01, 0));
			//matrix = glm::rotate(matrix, rotate, glm::vec3(0.0, 0.0, 0.0));
			//matrix = glm::translate(matrix, glm::vec3(0.0, 0.0, -0.5));
			shader.UniformMat4(matrix, "matrix");
			shader.UniformMat4(proj, "cam_proj");
			shader.UniformMat4(view, "cam_view");
			vao.draw(TRIANGLE);

			matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, glm::vec3(-1.5, 0.0, 0.0));
			matrix = glm::rotate(matrix, rotate, glm::vec3(0.01, 0.01, 0));
			shader.UniformMat4(matrix, "matrix");
			shader.UniformMat4(proj, "cam_proj");
			shader.UniformMat4(view, "cam_view");
			vao.draw(TRIANGLE);

			matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, glm::vec3(0.0, 1.5, 0.0));
			matrix = glm::rotate(matrix, rotate, glm::vec3(-0.01, 0.01, 0));
			shader.UniformMat4(matrix, "matrix");
			shader.UniformMat4(proj, "cam_proj");
			shader.UniformMat4(view, "cam_view");
			vao.draw(TRIANGLE);

			matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, glm::vec3(0.0, -1.5, 0.0));
			matrix = glm::rotate(matrix, rotate, glm::vec3(0.01, 0.01, 0));
			shader.UniformMat4(matrix, "matrix");
			shader.UniformMat4(proj, "cam_proj");
			shader.UniformMat4(view, "cam_view");
			vao.draw(TRIANGLE);

			matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, glm::vec3(1.5, 0.0, 0.0));
			matrix = glm::rotate(matrix, rotate, glm::vec3(-0.01, 0.01, 0));
			shader.UniformMat4(matrix, "matrix");
			shader.UniformMat4(proj, "cam_proj");
			shader.UniformMat4(view, "cam_view");
			vao.draw(TRIANGLE);

			//triangle.draw(TRIANGLE);
#pragma endregion RENDER_CUBES

			buffer_1.render();
			gui.render();
			
			win.swapBuffers(true);
			win.setSizeBuffer(win.width, win.height);
		}

		//fonts::Text2D::DeleteALL();
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
}