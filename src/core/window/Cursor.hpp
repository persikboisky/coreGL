#ifndef SRC_CORE_WINDOW_CURSOR_HPP_
#define SRC_CORE_WINDOW_CURSOR_HPP_

#include <vector>

enum Cursor_mode;
struct GLFWwindow;
struct GLFWcursor;

struct cursor
{
	static double getCordCursorX(GLFWwindow* window);
	static double getCordCursorY(GLFWwindow* window);
	static void getCordCursor(GLFWwindow* window, double& x, double& y);
};

class Cursor
{
private:
	GLFWwindow* window;

public:
	static class custom_cursor
	{
	private:
		GLFWcursor* cursor_objs;
		GLFWwindow& addrWindow;

	public:
		custom_cursor(const char* pathToPng, int x, int y, GLFWwindow* window);
		~custom_cursor();
		void use(GLFWwindow* window = nullptr);
	};

	Cursor(GLFWwindow& addrWindow);
	~Cursor();

	void setCursorMode(int mode);
	void showCursor(bool flag);
	void disableCursor(bool flag);
	void setPosition(double x, double y);

	double getCordCursorX();
	double getCordCursorY();
	void getCordCursor(double& x, double& y);

	custom_cursor* create(const char* path, int x = 0, int y = 0);
};

#endif // !SRC_CORE_WINDOW_CURSOR_HPP_
