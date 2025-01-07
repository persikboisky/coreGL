#ifndef SRC_WINDOW_CURSOR_HPP_
#define SRC_WINDOW_CURSOR_HPP_

struct cursor
{
	static void setCursorMode(int mode);
	static void showCursor(bool flag);
	static void disableCursor(bool flag);
	static void setPosition(double x, double y);
};

#endif // SRC_WINDOW_CURSOR_HPP_
