#include "Cursor.hpp"
#include "../file/png.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

extern bool coreInfo;

double cursor::getCordCursorX(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return x;
}

double cursor::getCordCursorY(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return y;
}

void cursor::getCordCursor(GLFWwindow* window, double& x, double& y)
{
	glfwGetCursorPos(window, &x, &y);
}

Cursor::Cursor(GLFWwindow& addrWindow) : window(&addrWindow)
{

}

Cursor::~Cursor()
{
	//this->DeleteALL();
}

void Cursor::setCursorMode(int mode)
{
	glfwSetInputMode(this->window, GLFW_CURSOR, mode);
}

void Cursor::showCursor(bool flag)
{
	if (!flag) setCursorMode(GLFW_CURSOR_HIDDEN);
	else setCursorMode(GLFW_CURSOR_NORMAL);
}

void Cursor::disableCursor(bool flag)
{
	if (flag) setCursorMode(GLFW_CURSOR_DISABLED);
	else setCursorMode(GLFW_CURSOR_NORMAL);
}

void Cursor::setPosition(double x, double y)
{
	glfwSetCursorPos(this->window, x, y);
}

double Cursor::getCordCursorX()
{
	double x, y;
	glfwGetCursorPos(this->window, &x, &y);
	return x;
}

double Cursor::getCordCursorY()
{
	double x, y;
	glfwGetCursorPos(this->window, &x, &y);
	return y;
}

void Cursor::getCordCursor(double& x, double& y)
{
	glfwGetCursorPos(this->window, &x, &y);
}

Cursor::custom_cursor::custom_cursor(const char* pathToPng, int x, int y, GLFWwindow* window) : addrWindow(*window)
{
	unsigned char* png = png::load(pathToPng);

	GLFWimage* img = new GLFWimage;
	img->height = png::height;
	img->width = png::width;
	img->pixels = &png[0];

	this->cursor_objs = glfwCreateCursor(img, x, y);

	if (this->cursor_objs == nullptr)
	{
		std::cerr << "Failed: create cursor obj";
		throw "FAILED_CREATE_CURSOR_OBJ";
	}

	if (coreInfo) std::cout << "OK: created cursor > " << pathToPng << std::endl;
}

Cursor::custom_cursor::~custom_cursor()
{
	glfwDestroyCursor(this->cursor_objs);
}

Cursor::custom_cursor* Cursor::create(const char* path, int x, int y)
{
	return new Cursor::custom_cursor(path, x, y, this->window);
}

void Cursor::custom_cursor::use(GLFWwindow* window)
{
	if (window == nullptr)
	{
		window = &addrWindow;
	}
	glfwSetCursor(window, this->cursor_objs);
}