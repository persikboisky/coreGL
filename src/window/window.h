#ifndef SRC_WINDOW_WINDOW_H_
#define SRC_WINDOW_WINDOW_H_

class GLFWwindow;

struct window
{
	static GLFWwindow* Window;
	static int width;
	static int height;
	static int create(const char* title, int width, int height);
	static void setIcon(const char* path);
	static void swapBuffers();
	static void close();
	static void destroy();
};

#endif // !SRC_WINDOW_WINDOW_H_
