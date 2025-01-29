#include "Cursor.h"
#include <GLFW/glfw3.h>

Cursor::Cursor(GLFWwindow& addrWindow) : window(&addrWindow)
{

}

void Cursor::setCursorMode(int mode)
{
	glfwSetInputMode(this->window, GLFW_CURSOR, mode);
}

void Cursor::showCursor(bool flag)
{
	if (flag) setCursorMode(GLFW_CURSOR_HIDDEN);
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