#ifndef SRC_CORE_WINDOW_CURSOR_H
#define SRC_CORE_WINDOW_CURSOR_H

enum Cursor_mode;
struct GLFWwindow;

class Cursor 
{
private:
	GLFWwindow* window;

public:
	Cursor(GLFWwindow& addrWindow);

	void setCursorMode(int mode);
	void showCursor(bool flag);
	void disableCursor(bool flag);
	void setPosition(double x, double y);

	double getCordCursorX();
	double getCordCursorY();
	void getCordCursor(double& x, double& y);
};

#endif // !SRC_CORE_WINDOW_CURSOR_H
