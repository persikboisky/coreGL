## Окна



Для работы с окном(окнами) предусмотрен класс Window,\
и да в ядре можно создовать не одно окно, а несколька

```cpp
// у меня в примере "win" это название объекта окна,
// вы можете использовать любое другое название

Window win(const char* title, int width, int height, bool resizable = true);
// этот конструктор создаёт объект окна и само окно с указанным
// названием, и размером, есть ещё необязательный параметр: 
// разрешить изменять размер окна с помощью курсора

win.setIcon(const char* path);
// устанавливаем png иконку для окна, принимает путь к файлу

win.setContext();
// устанавливает данный объект в качестве контекста(то где мы рендерим)

win.isContext();
// если данное окно является контекстом, возвращает(bool) true, иначе false

win.swapBuffers(
    bool fill = true,  // разрешить закрашивать буфер кадра указанным цветом
    float red = 0,     // красный канал (от 0.0f до 255.0f)
    float green = 0,   // зелённый канал (от 0.0f до 255.0f)
    float blue = 0,    // синий канал (от 0.0f до 255.0f)
    float alhpa = 1.0f // альфа канал (от 0.0f до 255.0f)
);
// сменяет буферы кадра
```

> [!TIP]
> В openGL два буфера на одном мы рисуем, другой отображается на экране\
> win.swapBuffers() - меняяет буферы\
> Теперь отображается тот, на котором мы рисовали,\
> а рисуем мы на том, который отображался\
> Расписал как мог :)

```cpp
win.setSizeBuffer(int width, int height);
// устанавливает размер буфера кадра

win.width, win.height;
// переменные(тип int), которые хранят текущий размер окна,
// размер перезаписывается при каждом вызове win.swapBuffers();

win.close();
// вызывает событие закрытия окна (не удаляет окно)

win.event->update();
// обновляет буфер эвентов

win.event->close();
// возвращает(bool) true, если сработает эвент закрытия окна
// (кто то нажмёт на крестик или вызавет функцию win.close(); ), иначе false

win.event->GetMouseLeftButton();
// возвращает(bool) true если нажата ЛКМ, иначе false

win.event->GetMouseRightButton();
// возвращает true если нажата ПКМ, иначе false

win.event->getKey(Key_code key);
win.event->getKey(int key);
// обе функции возвращают(bool) true если нажата клавиша
// верхняя функция (не доделана, она поддерживает не все клавиши)
// принимает названия K_ESCAPE, K_W и т.д.
// нижняя принимает номер клавиши в стандарте библиотеки GLFW

win.cursor->setCursorMode(int mode);
// устанавливает режим курсора, номер режима соответствует стандарту библиотеки GLFW
// (ни разу не использовал эту функцию:) )

win.cursor->showCursor(bool flag);
// делает курсор прозрачным если передать true

win.cursor->disableCursor(bool flag);
// выключает курсор ели передать true
// если русским языком, она убирает ограничения(края монитора) для курсора, 
// его можно будет передвигать за зону видимости

win.cursor->setPosition(double x, double y);
// устанавливает курсор на указанные координаты

```
>[!TIP]
> Диапазон координат курсора:\
> по осиX от 0 до win.width\
> по осиY от 0 до win.height
```cpp

win.cursor->getCordCursorX();
// возвращает(double) координаты курсора по x

win.cursor->getCordCursorY();
// возвращает(double) координаты курсора по y

win.cursor->getCordCursor(double& x, double& y);
// передаёт координаты курсора в переменные по их адресу

// c - объект курсора, можно любое другое название
// пример как создать кастомный курсор
Cursor::custom_cursor* c = win.cursor->create(
    const char* path, int x = 0, int y = 0
);
// этот конструктор принимает путь к png картинке и координаты

c->use();
// устанавливает созданный курсор в качестве основного
```

Пример кода:
```cpp
#include "core/core.hpp"

int main()
{
	try
	{
		core::Init();
		
		Window win("first window", 1280, 720);
		win.setContext();

		while (!win.event->close())
		{
			win.event->update();

			// тут будем что-то рисовать в будущем

			win.swapBuffers();
			win.setSizeBuffer(win.width, win.height);
		}
	}
	catch (...)
	{
		core::Terminate();
		return -1;
	}

	core::Terminate();
	return 0;
}
```

+ [дальше](GraphicСooker.md)
+ [назад](core.md) 
+ [в оглавление](manual.md)