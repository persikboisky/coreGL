# Ядро

> [!NOTE]
> ```sh
> Ядро coreGL это мой проект написанный на c++
> Главная цель - уменьшить кол-во кода
> Библиотеки использованные мной: openGL, glfw, glew, glm, openAL, stb_image
> ```

> [!WARNING]
>```sh
> Требуется windows x64
> Работает по умолчанию на версии openGL 4.6(но это можно поменять)
>```

## Использование ядра
```sh
самый простой способ это открыть проект в visual studio(файл core.sh)
второй способ для от чайных это скопировать содержимое из src/core в свой проект

и в том, и в другом случае для использования функций ядра, надо 
подключать заголовочный файл src/core/core.hpp
```

## Настройка проекта
>[!NOTE]
>```sh
> если вы используете visual studio, убедитесь что режим компиляции - reales, а не debug
>```

+ в заголовочный файле src/core/core.hpp можно произвести настройку ядра:
```cpp
4  // версия openGL(4.6), не советую изменять, пока не прочитаете про шейдеры
5  constexpr unsigned short VERSION_MAJOR = 4;
6  constexpr unsigned short VERSION_MINOR = 6;
7 
8  // разрешить изменения размера окна(окон)
9  constexpr bool WINDOW_RESIZABLE = true;
10
11 // разрешить получение информации о состояние разных процессов
12 constexpr bool CORE_INFO = true;
```

## структура ядра
:open_file_folder: core 
>:file_folder: audio\
>:file_folder: data\
>:file_folder: graphics\
>:file_folder: util\
>:file_folder: window\
>:page_facing_up: core.hpp

core.hpp это заголовочный файл, включает все инструменты ядра\
audio, data, file, graphics, util, window - это системы ядра, на каждой из них мы остановимся ниже

## инициализация ядра
``` cpp
#include "core/core.hpp"

int main()
{
	try
	{
        // инициализирует ядро
		core::Init();
		
		// ваш код
	}
	catch (...)
	{
        // освобождает память и выключает ядро
		core::Terminate();
		return -1;
	}

    // освобождает память и выключает ядро
    core::Terminate();
	return 0;
}
```

``` cpp
core::GetTime();
// возвращает(double) время в секундах с момента инициализации ядра
```


+ [дальше](window.md)
+ [в оглавление](manual.md)