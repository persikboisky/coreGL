#ifndef SRC_CORE_CORE_H_
#define SRC_CORE_CORE_H_

#define VERSION_MAJOR 4
#define VERSION_MINOR 6
#define WINDOW_RESIZABLE true

#include <GL/glew.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <thread>
#include <iostream>
#include "window/Window.hpp"
#include "window/Event.hpp"
#include "window/Cursor.hpp"
#include "file/png.hpp"
#include "file/text.hpp"
#include "file/toml_file.hpp"
#include "file/obj.hpp"
#include "file/mtl.hpp"
#include "file/wav.hpp"
#include "graphics/vao.hpp"
#include "graphics/shader.hpp"
#include "graphics/Camera.hpp"
#include "graphics/GUI/GUI.hpp"
#include "graphics/GUI/style.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"
#include "util/vector.hpp"
#include "util/string.hpp"
#include "util/array.hpp"
#include "audio/audio.hpp"
#include "audio/Device.hpp"
#include "audio/buffer.hpp"
#include "audio/source.hpp"

enum primitive {
	TRIANGLE_STRIP = GL_TRIANGLES,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	POINT = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	QUARD = GL_QUADS
};

enum Key_code {
	K_W = GLFW_KEY_W,
	K_S = GLFW_KEY_S,
	K_A = GLFW_KEY_A,
	K_D = GLFW_KEY_D,
	K_F1 = GLFW_KEY_F1,
	K_SPACE = GLFW_KEY_SPACE,
	K_ESCAPE = GLFW_KEY_ESCAPE,
	K_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
	K_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL
};

enum Cursor_mode {

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