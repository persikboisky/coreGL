#include "core/core.hpp"

int main()
{
	core::Init();

	try
	{

		Window window("opengl", 1280, 720);
		window.setContext();

		Cursor::custom_cursor* c = window.cursor->create("cursor.png", 0, 0);
		c->use();

		VAO vao({
			-0.5, -0.5,
			-0.5, 0.5,
			0.5, 0.5,
			0.5,-0.5
		}, 2);
		vao.addAttribute(0, 2, 0);

		Shader s("v.glsl", "f.glsl");
		s.use();

		window.cursor->disableCursor(true);

		while (true)
		{
			window.event->update();
			if (window.event->getKey(K_ESCAPE))
			{
				break;
			}

			vao.draw(QUADS);
			window.swapBuffers(true, 0, 0, 0, 1);
		}

	}
	catch (const char* error)
	{
		core::Terminate();
		return -1;
	}

	audio::source::DeleteALL();
	audio::buffer::DeleteALL();
	core::Terminate();
	return 0;
}