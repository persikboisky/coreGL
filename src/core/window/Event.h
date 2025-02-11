#ifndef SRC_CORE_WINDOW_EVENT_H_
#define SRC_CORE_WINDOW_EVENT_H_

#define MAX_KEY_CODE 360

enum Key_code;
struct GLFWwindow;
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

class Event
{
private:
	GLFWwindow* window;
	//void key_callbac(GLFWwindow* window, int key, int scancode, int action, int mods);
	void setCallbackKey(GLFWwindow* window, GLFWkeyfun callback);
	//static bool key() для взаимодейсвия с массивом

public:
	Event(GLFWwindow& addrWindow);
	
	void update();
	bool close();
	bool GetMouseLeftButton();
	bool GetMouseRightButton();
	bool getKey(Key_code key);
};

#endif // !SRC_CORE_WINDOW_EVENT_H_