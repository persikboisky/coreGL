## Build in macOS and Linux
>[!NOTE]
>
> Я вам ни чем не помогу, могу дать только список нужных библиотек:
> glew, glfw, glm, stb, nlohmann, opengl32(Должна быть установлена по умолчанию драйвером)


## Build in Windows
>[!NOTE]
>[Библиотеки](https://github.com/persikboisky/libForOpengl)
>
> Рекомендую: Visual Studio

```sh
1. скачиваем и разархивируем архив
2. открываем проект файл openGL.sln (должна быть установлена Visual Studio)
3. проверяем что бы сверху стояло Reales x64 (если не стоит, то устанавливаем)
4. запускаем (Вы увидите вращающейся треугольник)
5. теперь можете писать свои проекты

```
> [!WARNING]
>```sh
> Требуется ос win x64
> Работает по умолчанию на версии openGL 4.6
>```

> [!TIP]
>
> ```sh
> Чтобы указать другую версию openGL заходим в файл window.cpp (src/engineSoft/window/window.cpp)
> Находим эти строки (они в начале), и указываем версию
> #define VERSION_MAJOR первое число
> #define VERSION_MINOR второе число
> ```

## Системы движка
>[!NOTE]
>```sh
> в папке src/engineSoft расположены все системы и под системы движка
> в файле src/main.cpp написан демонстрационный код
> вся ниже предоставленная информация рассчитана на то, что вы не будете лезть в папку src/engineSoft
> для подключения функций движка, есть заголовочный файл по пути src/engineSoft/engine.hpp
> некоторые функции могут вызывать исключения, я ниже опишу значение всех исключений(вызвать их почти невозможно:))
>```

## система window, структура window
```sh
window::create(const char* title, int width, int height) - Создаёт окно
title - заголовок окна
width - ширина окна
height - высота окна

ИСКЛЮЧЕНИЯ:
1. "GLFW_INIT_FAILED" - проблема с библиотекой glfw
2. "FAILED_CREATE_WINDOW" - не удалось создать окно
3. "FAILED_INIT_GLEW" - проблема с библиотекой glew
```
```sh
window::destroy() - удаляет окно и освобождает ресурсы библиотек из озу

window::width - хранит текущую ширину(int) окна
window::height - хранит текущую высоту(int) окна

void window::setIcon(const char* path) - устанавливает иконку окна
принимает путь к png файлу

window::close() - закрывает окно
window::swapBuffer() - сменяет буфер
```
> [!TIP]
> в openGL двойная буферизация, то есть на одном мы рисуем, а второй выводится на экран


## система window, пространство имён event
```sh
event::init() - инициализирует систему эвентов (обязательно)
event::update() - проверяет на наличие эвентов и обновляет систему эвентов
event::closeWindow() - проверяет окно на эвент закрытия, если окна закрывается,
то эта функция вернёт true, иначе false

event::key::getKey(int keyCode) - возвращает true, если клавиша с номером, переданным в функцию, нажата
event::mouse::GetMouseCordX() - возвраощает кординаты(double) курсора по оси-x
event::mouse::GetMouseCordY() - возвраощает кординаты(double) курсора по оси-y

event::mouse::GetMouseLeftButton() - возвращает true, если нажата левая кнопка мыши
event::mouse::GetMouseRightButton() - возвращает true, если нажата правая кнопка мыши
```

## система window, структура cursor
```sh
cursor::setCursorMode(int mode) - включает выбранный режим курсора
cursor::showCursor(bool flag) - если функция принимает true, то курсор становится не видимым
cursor::disableCursor(bool flag) - если функция принимает true, то курсор выключается
cursor::setPosition(double x, double y) - устанавливает курсор на указанные кординаты
```

## ситема graphics, структура vao
```sh
vao::create(float data[], int sizeOfByte) - зодаёт буффер вершинных аттрибутов и возвращает(unsigned int) дескриптор
ИСКЛЮЧЕНИЕ:
"FAILED_CREATE_VAO" - это исключение означает - ошибку создания vao,
 может быть вызвана старой версией openGL, старыми драйверами, или проблемной библиотекой,
 а также если вы создаёте vao до создания окна

vao::addAttribute(unsigned int id, int index, int n, int size, int indentation) создаёт вершинный атрибут,
принимает дескриптор vao, номер вершинного атрибута (это то что прописывается в шейдере),
количество элементов для атрибута, количество элементов на одну вершину, отступ

vao::draw(primitiveENUM primitive, unsigned int id, int first_vert, int finish_vert)
рисует примитив(ы), принимает название примитива, дескриптор vao, номер первой вершины, номе последней вершины

ИСКЛЮЧЕНИЕ:
"FAILED_BIND_VAO" - это исключение появится, если openGL не видит vao по указанному дескриптору 

vao::Delete(unsigned int id) удаляет vao, принимает дескриптор
vao::DeleteALL() удаляет все vao
```















