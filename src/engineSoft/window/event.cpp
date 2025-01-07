#include "event.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>

bool Key[MAX_KEY_CODE];

void key_callbac(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	if (action == GLFW_PRESS)
	{
		Key[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		Key[key] = false;
	}
}

void event::init()
{ 
	glfwSetKeyCallback(window::Window, key_callbac);
}

void event::update()
{
    glfwPollEvents();
}

bool event::closeWindow()
{
    return glfwWindowShouldClose(window::Window);
}

bool event::key::getKey(int keyCode)
{
	if (keyCode >= MAX_KEY_CODE) std::cerr << "there is no such key in the buffer" << std::endl;

	else return Key[keyCode];
}

double event::mouse::GetMouseCordX()
{
	double mouseX, mouseY;
	glfwGetCursorPos(window::Window, &mouseX, &mouseY);
	return mouseX;
}

double event::mouse::GetMouseCordY()
{
	double mouseX, mouseY;
	glfwGetCursorPos(window::Window, &mouseX, &mouseY);
	return mouseY;
}

bool event::mouse::GetMouseLeftButton()
{
	return glfwGetMouseButton(window::Window, GLFW_MOUSE_BUTTON_LEFT);
}

bool event::mouse::GetMouseRightButton()
{
	return glfwGetMouseButton(window::Window, GLFW_MOUSE_BUTTON_RIGHT);
}