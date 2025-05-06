# Ядро

> [!NOTE]
> ```sh
> Ядро coreGL это мой проект написанный на c++
> Главная цель - уростить разроботку приложений
> Библиотеки использованные мной: openGL, glfw, glew, openAL, stb_image
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

+ в заголовочный файле src/core/config.hpp можно произвести настройку ядра:
```cpp
// версия openGL(4.6)
constexpr unsigned short VERSION_MAJOR = 4;
constexpr unsigned short VERSION_MINOR = 6;

// по умолчанию разрешает изменять размер окна(окон)
constexpr bool WINDOW_RESIZABLE = true;

// разрешить получение информации о состояние различных процессов
constexpr bool CORE_INFO = true;

```

## структура ядра
:open_file_folder: core 
>:file_folder: audio\
>:file_folder: graphics\
>>:file_folder: math\
>:file_folder: util\
>:file_folder: window\
>:page_facing_up: config.hpp
>:page_facing_up: core.hpp

core.hpp это заголовочный файл, включает все инструменты ядра\
audio, file, graphics, math, util, window - это системы ядра, на каждой из них мы остановимся дальше

## инициализация ядра
``` cpp
// для vs
#include <core/core.hpp>

// в остальных случаях пишм путь к файлу core.hpp

using namespace core;
using namespace core::math;

int main()
{
	try
	{
        // инициализирует ядро
		Core::Init();
		
		// ваш код
	}
	catch (...)
	{
        // освобождает память и выключает ядро
		Core::Terminate();
		return -1;
	}

    // освобождает память и выключает ядро
    Core::Terminate();
    return 0;
}
```

``` cpp
Core::GetTime();
// возвращает(double) время в секундах с момента инициализации ядра
```


+ [дальше](window.md)
+ [в оглавление](manual.md)
