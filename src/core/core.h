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
#include "graphics/vao.h"
#include "graphics/shader.h"
#include "graphics/Camera.h"
#include "graphics/texture.h"
#include "util/vector.h"

enum primitive {
	TRIANGLE = GL_TRIANGLES,
	POINT = GL_POINT
};

struct core
{
	static void Init();
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

#endif // !SRC_CORE_CORE_H_