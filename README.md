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
1. Скачиваем библиотеки по верхней ссылке
2. копируем папку lib в папку проекта(openGL)
3. открываем проект в VS (openGL.sln)
4. проверяем что бы сверху стояло Reales x64
5. запускаем
```
> [!WARNING]
>
> Проект настроен для сборки на winX64 и openGL 4.6

> [!TIP]
>
> ```sh
> Чтобы указать другую версию openGL заходим в файл Window.cpp (src/window/Window.cpp)
> Находим эти строки (они в начале), и указываем версию
> #define VERSION_MAJOR первое число
> #define VERSION_MINOR второе число
> ```

## Системы движка
>[!NOTE]
>```sh
> вся ниже предоставленная информация рассчитана на то, что вы будете использовать функции в main
> все функции имеют стиль записи (НазваниеСистемы::функция())
>```

## система Window
```sh
Window::initializateWindow(name, width, height) - Создаёт окно
name - заголовок окна(char*)
width - ширина окна(int)
height - высота окна(int)
```
```sh
Window::setWindowIcon(unsigned char* img, int width, int height) - устанавливает иконку окна
принимает строчку изображения, ширину изображения, высоту изображения

Window::terminate() - удаляет окно
Window::isCloseWindow() - возвращает true при закрытие окна

Window::setShouldClose(flag) - закрывает окно
если в flag передать true то окно закроется

Window::swapBuffer() - сменяет буфер
```
> [!TIP]
> в openGL двойная буферизация, то есть на одном мы рисуем, а второй выводится на экран 

## Система Shader
```sh
shader::getShaderProgram(const char* frag, const char* vert);
возвращает дескриптор шейдерной программы и создаёт её, принимает путь к шейдерам

shader::use(unsigned int id);
включает шейдерную программу, принимает её дескриптор

shader::Delete(unsigned int id);
удаляет шейдерную программу, принимает её дескриптор

shader::setValueUniform(unsigned int id, const float value, const char* name);
shader::setValueUniform(unsigned int id, glm::mat4 matrix, const char* name);
обе функции имею одинаковые названия,
первая передаёт float значение в uniform переменную в шейдере,
вторая передаёт матрицу в uniform переменную в шейдере.
Принимают дескриптор шейдерной программы, значение, название переменной в шейдере
```

## Система JSON
```sh
JSON::getValueFromJSON(const char* PATH, const char* object)
возвращает значение записанное в json, работает только с int переменными, принимает путь и название объекта

```
> [!NOTE]
> ```sh
> файл должен иметь такую структуру
>
> 
> {
>  "название объекта": значениеТипа(int),
>}
> ```

## Система VAO
```sh
VAO название; - создаёт vao объект с указанным названием

название.bind() - включает vao
название.debind() - выключает vao

addVBO({
координаты вершин
}) - добавляет vbo в vao

название.draw(кол-во вершин) - рисует треугольник(и)
3 вершины - один треугольник
6 вершин - два треугольника
и тд.
```

## Система Event
```sh
Event::update() - обновляет буфер эвентов (проверяет эвенты)

Event::Mouse::GetMouseCordY() - возвращает позицию мышки по осиY
возвращает значение double

Event::Mouse::GetMouseCordX() - возвращает позицию мышки по осиX
возвращает значение double

Event::Mouse::GetMouseRightButton()
возвращает true если нажать на правую кнопку мыши

Event::Mouse::GetMouseLeftButton()
возвращает true если нажать на левую кнопку мыши

Event::Key::getKey[номер клавиши]
возвращает true если клавиша нажата, и false если отпущена
```

## Система PNG
```sh
png::loadPNG(const char* PATH);
принимае путь к png изображению, возвращает строку этого изображения

png::width, png::height, png::channels;
хранят ширину, высоту, кол-во каналов в изображении
```
> [!NOTE]
> при загрузки нового изображения, все переменные структуры png будут перезаписана

















