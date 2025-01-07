#ifndef SRC_WINDOW_EVENT_H_
#define SRC_WINDOW_EVENT_H_

#define MAX_KEY_CODE 360

namespace event
{
	void init();
	void update();
	bool closeWindow();
	struct key;
	struct mouse;
}

struct event::key
{
	static bool getKey(int keyCode);
};

struct event::mouse
{
	static double GetMouseCordY();
	static double GetMouseCordX();
	static bool GetMouseLeftButton();
	static bool GetMouseRightButton();
};

#endif //SRC_WINDOW_EVENT_H_
