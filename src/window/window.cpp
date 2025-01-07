#define VERSION_MAJOR 4
#define VERSION_MINOR 6
#define WINDOW_RESIZABLE true

#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../load/png.h"

GLFWwindow* window::Window;
int window::width;
int window::height;

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	window::width = width;
	window::height = height;
}

int window::create(const char* title, int width, int height)
{
	if (glfwInit())
	{
		std::cout << "OK: initializate GLFW" << std::endl;
	}
	else
	{
		std::cerr << "FAILED: initializate GLFW" << std::endl;
		throw "GLFW_INIT_FAILED";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, WINDOW_RESIZABLE);

	Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (Window == nullptr)
	{
		std::cerr << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		throw "FAILED_CREATE_WINDOW";
	}
	else
	{
		std::cout << "OK: to create GLFW Window" << std::endl;
	}

	window::width = width;
	window::height = height;

	glfwMakeContextCurrent(Window);

	glewExperimental = GL_TRUE;
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		if (glewErr == GLEW_ERROR_NO_GLX_DISPLAY)
		{
			std::cerr << "Failed initializate GLEW error 240" << std::endl;
		}
		else
		{
			std::cerr << "Failed initializate GLEW" << std::endl;
			return -1;
		}
		throw "FAILED_INIT_GLEW";
	}
	else
	{
		std::cout << "OK: initializate GLEW" << std::endl;
	}

	glfwSetWindowSizeCallback(Window, window_size_callback);
	glViewport(0, 0, width, height);
	return 1;
}

void window::setIcon(const char* path)
{
	GLFWimage images[1];

	int width, height, channels;
	unsigned char* img = png::load(path, width, height, channels);

	images[0].width = width;
	images[0].height = height;
	images[0].pixels = img;

	glfwSetWindowIcon(Window, 1, images);
	free(images[0].pixels);
}

void window::swapBuffers()
{
	glfwSwapBuffers(Window);
}

void window::close()
{
	glfwSetWindowShouldClose(Window, true);
}

void window::destroy()
{
	glfwDestroyWindow(Window);
	glfwTerminate();
}