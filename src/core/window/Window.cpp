#include "Window.hpp"
#include "../file/png.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

extern bool coreInfo;

inline void Window::getSizeWindow()
{
	glfwGetWindowSize(this->window, &this->width, &this->height);
}

Window::Window(const char* title, int width, int height, bool resizable) : width(width), height(height)
{
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (this->window == nullptr)
	{
		std::cerr << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		throw "FAILED_CREATE_WINDOW";
	}

	if (coreInfo)
	{
		std::cout << "[" << glfwGetTime() << "] " << "OK: to create GLFW Window" << std::endl;
	}

	this->Init();
}	
	
Window::~Window()
{
	delete this->cursor;
	delete this->event;
	glfwDestroyWindow(this->window);
}

void Window::swapBuffers(bool fill, float red, float green, float blue, float alhpa)
{
	glfwSwapBuffers(this->window);
	this->getSizeWindow();

	if (fill)
	{
		glClearColor(
			red / 255.0f, 
			green / 255.0f, 
			blue / 255.0f, 
			alhpa / 255.0f
		);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}

void Window::setIcon(const char* path)
{
	GLFWimage images[1];

	unsigned char* img = png::load(path);

	images[0].width = png::width;
	images[0].height = png::height;
	images[0].pixels = img;

	glfwSetWindowIcon(this->window, 1, images);
	free(images[0].pixels);
}

void Window::close()
{
	glfwSetWindowShouldClose(this->window, true);
}

void Window::setContext()
{
	glfwMakeContextCurrent(this->window);
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
		}
		throw "FAILED_INIT_GLEW";
	}
	glEnable(GL_DEPTH_TEST);
}

void Window::setSizeBuffer(int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Window::isContext()
{
	if (this->window == glfwGetCurrentContext())
	{
		return true;
	}
	return false;
}
