#include "Event.h"
#include <GLFW/glfw3.h>
#include <iostream>

bool Key[MAX_KEY_CODE];

void key_callbac(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void Event::setCallbackKey(GLFWwindow* window, GLFWkeyfun callback)
{
	glfwSetKeyCallback(window, callback);
}

Event::Event(GLFWwindow &addrWindow) : window(&addrWindow)
{
	this->setCallbackKey(this->window, key_callbac);
	//glfwSetKeyCallback(this->window, key_callbac);
}

void Event::update()
{
	glfwPollEvents();
}

bool Event::close()
{
	return glfwWindowShouldClose(this->window);
}

bool Event::GetMouseLeftButton()
{
	return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT);
}

bool Event::GetMouseRightButton()
{
	return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT);
}

bool Event::getKey(int keyCode)
{
	if (keyCode >= MAX_KEY_CODE) std::cerr << "there is no such key in the buffer" << std::endl;

	else return Key[keyCode];
}