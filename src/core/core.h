#ifndef SRC_CORE_CORE_H_
#define SRC_CORE_CORE_H_

#define VERSION_MAJOR 4
#define VERSION_MINOR 6
#define WINDOW_RESIZABLE true

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window/Window.h"
#include "window/Event.h"
#include "window/Cursor.h"
#include "file/png.h"
#include "file/text.h"
#include "file/toml_file.h"
#include "file/obj.h"
#include "graphics/vao.h"
#include "graphics/shader.h"
#include "graphics/Camera.h"
#include "graphics/texture.h"
#include "util/vector.h"
#include "util/string.h"

enum primitive {
	TRIANGLE_STRIP = GL_TRIANGLES,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	POINT = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	QUARD = GL_QUADS
};

enum Key_code {
	W = GLFW_KEY_W,
	S = GLFW_KEY_S,
	A = GLFW_KEY_A,
	D = GLFW_KEY_D,
	F1 = GLFW_KEY_F1,
	SPACE = GLFW_KEY_SPACE,
	ESCAPE = GLFW_KEY_ESCAPE,
	LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
	LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL
};

struct core
{
	static void Init();
	static void Terminate();
};

void core::Init()
{
	if (glfwInit())
	{
		std::cout << "OK init glfw" << std::endl;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, WINDOW_RESIZABLE);
	}
	else
	{
		std::cerr << "Failed init glfw" << std::endl;
		throw "FAILED_INIT_GLFW";
	}
}

void core::Terminate()
{
	glfwTerminate();
}

#endif // !SRC_CORE_CORE_H_