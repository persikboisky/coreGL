#ifndef SRC_CORE_CORE_H_
#define SRC_CORE_CORE_H_

// версия openGL(4.6)
constexpr unsigned short VERSION_MAJOR = 4;
constexpr unsigned short VERSION_MINOR = 6;

// разрешить изменения размера окна(окон)
constexpr bool WINDOW_RESIZABLE = true;

// разрешить получение информации о состояние разных процессов
constexpr bool CORE_INFO = true;

// библиотеки
#include <GL/glew.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>
#include <iostream>

// моё говно
#include "window/Window.hpp"
#include "window/Event.hpp"
#include "window/Cursor.hpp"
#include "util/vector.hpp"
#include "util/string.hpp"
#include "util/array.hpp"
#include "util/structs.hpp"
#include "util/math.hpp"
#include "file/png.hpp"
#include "file/text.hpp"
#include "file/toml_file.hpp"
#include "file/obj_loaders.hpp"
#include "file/mtl.hpp"
#include "file/wav.hpp"
#include "graphics/commons/vao.hpp"
#include "graphics/commons/fbo.hpp"
#include "graphics/commons/ebo.hpp"
#include "graphics/commons/shader.hpp"
#include "graphics/commons/Camera.hpp"
#include "graphics/commons/texture.hpp"
#include "graphics/commons/font.hpp"
#include "graphics/commons/styleText.hpp"
#include "graphics/obj/obj_compile.hpp"
#include "graphics/obj/OBJ.hpp"
#include "graphics/obj/obj_mesh.hpp"
#include "graphics/gui/GUI.hpp"
#include "graphics/gui/GUI_Style.hpp"
#include "graphics/commons/BufferText2D.hpp"
#include "audio/audio.hpp"
#include "audio/Device.hpp"
#include "audio/buffer.hpp"
#include "audio/source.hpp"
#include "data/time.hpp"
#include "data/info.hpp"

bool coreInfo = CORE_INFO;

enum primitive {
	TRIANGLE = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	QUADS = GL_QUADS,
	QUADS_STRIP = GL_QUAD_STRIP,
	POLYGON = GL_POLYGON,
	POINT = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP
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
	//static Time::Date* date;

	static void Init();
	static void Terminate();
	static double GetTime();
};

void core::Init()
{
	//core::date = new Time::Date();

	if (!glfwInit())
	{
		std::cerr << "Failed init glfw" << std::endl;
		throw "FAILED_INIT_GLFW";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, WINDOW_RESIZABLE);

	if (coreInfo) std::cout << "[0.0]      " << "OK: init glfw" << std::endl;
}

void core::Terminate()
{
	shader::DeleteALL();
	vao::DeleteALL();
	ebo::DeleteALL();
	mtl::Delete();
	texture::DeleteALL();
	//fonts::Text2D::DeleteALL();
	                                     
	glfwTerminate();
	//delete date;
}

double core::GetTime()
{
	return glfwGetTime();
}

#endif // !SRC_CORE_CORE_H_