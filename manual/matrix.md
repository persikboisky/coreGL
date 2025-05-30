# Матрицы

## Матрицы, векторы, проецирование и библиотека GLM
Для начала напишем код который будет рисовать четырёхугольник

файл main.cpp
```cpp
#include "core/core.hpp"

// объявляем вектор с координатами и цветами вершин
std::vector<float> vertex
{
//     x    y    z    r    g    b
// первый треугольник
    -0.5, 0.5, 0.0, 1.0, 0.0, 0.0,
    -0.5,-0.5, 0.0, 0.0, 1.0, 0.0,
     0.5,-0.5, 0.0, 0.0, 0.0, 1.0,
// второй треугольник
    -0.5, 0.5, 0.0, 1.0, 0.0, 0.0,
     0.5,-0.5, 0.0, 0.0, 0.0, 1.0,
     0.5, 0.5, 0.0, 1.0, 1.0, 0.0
};
// обратите внимание что z = 0, это потому что openGL 
// без матриц преобразования рисует только 2D
// и если я сейчас напишу (z = любое число), то вы не увидите разницы

int main()
{
    try
    {
        core::Init();
        Window win("test", 1280, 720);
        win.setContext();

        // создаём vao
        // напомню что цифра 6 - обозначает кол-во элементов на вершину
        // у нас это три координаты: x, y, z и три канала цвета: r, g, b 
        VAO vao(vertex, 6);

        vao.addAttribute(0, 3, 0);
        // назначаем первым трём элементом вершины атрибут с индексом 0

        vao.addAttribute(1, 3, 3);
        // назначаем вторым трём элементом вершины атрибут с индексом 1

        Shader shader("vert.glsl", "frag.glsl");
        // загружаем шейдеры, код шейдера будет ниже

        // главный цикл, работает пока вы не нажмёте на крестик окна
        while (!win.event->close())
        {
            // обновляем объект событий
            win.event->update(); 

            // назначаем нашу шейдерную программу
            shader.use();

            // рисуем треугольник(точнее треугольники)
            vao.draw(TRIANGLE);
            // обратите внимание, что я не передаю кол-во вершин,
            // эта функция может их считать автоматически

            // сменяем буфер
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
vert.glsl - вершинный шейдер(название и расширение можно выбрать любое)
```glsl
#version 460 core
// версия glsl(у нас последняя как и openGL)

// подключаем атрибут 0 к вектору pos
layout (location = 0) in vec3 pos;

// подключаем атрибут 1 к вектору color
layout (location = 1) in vec3 color;

// отправляем вектор v_color в фрагментный шейдер
out vec3 v_color;

// главная функция
void main()
{
    // думаю понятно
    v_color = color;

    // говорим ГПУ что координаты вершины это вектор pos и 1.0
    // почему так? OpenGL использует четыре координаты x, y, z, w
    // w - это трансформация пока-что оставляем = 1
    gl_Position = vec4(pos, 1.0);
}
```

frag.glsl - фрагментный шейдер(название и расширение можно выбрать любое)
``` glsl
#version 460 core
// версия glsl(у нас последняя как и openGL)

// получаем вектор из вершинного шейдера
in vec3 v_color;

// отправляем f_color дальше по конвееру
// (это то вектор, который будет обозначать цвет вершины)
// он четырёхмерный red, green, blue, alpha
out vec4 f_color;

void main()
{
    f_color = vec4(v_color, 1.0f);
}
```

вот что вы должны получить
![](png/test2.png)

как вы могли заметить не смотря на равные координаты,\
наш четырёхугольник не похож на квадрат,\
это из за того, что буфер в openGL по x от -1 до 1 и по y от -1 до 1
что бы это исправить нужны матрицы преобразования

>[!NOTE]
> Что такое матрица - это математический объект, записываемый в виде прямоугольной таблицы\
> элементов кольца или поля (например, целых, действительных или комплексных чисел)
>
> Матрицы используются для преобразования координат вершин
>
> Вектор - это(забудьте то что вам говорит на математике) структура с\
> переменными, хранящими координаты

![](png/image-023.gif)\
вот пример умножения матрицы на вектор(таким образом\
можно вращать, перемещать, масштабировать, проецировать модель на экран)

Виды матриц:

1. единичная(при умножение на вектор, он не изменяется)\
![](png/image027.png)

2. матрица масштабирования\
![](png/i.png)\
где q - это коэффициент масштабирования по определённой оси

3. матрица перемещения\
![](png/transform.png)\
где t - значение на которое будет перемещён вектор по определённым осям

1. матрицы вращения:\
По оси X\
![](png/rotate_x.png)\
По оси Y\
![](png/rotate_y.png)\
По оси Z\
![](png/rotate_z.png)\
Обратите внимания на закрашенный линии, матрица\
выстраивается относительно этих линий\
Короче эти линии для наглядности и обозначают ту ось\
по которой будет происходить вращение\
A - угол поворота

Простите за кривые картинки, я не художник :)

Для того, что бы всё то что было написано сверху не запоминать в ядре есть библиотека GLM\
Теперь об этой библиотеки

файл main.cpp доработаем его
```cpp
            // назначаем нашу шейдерную программу
            shader.use();

            // создаём единичную матрицу matrix
            glm::mat4 matrix = glm::mat4(1.0f);

            // отправляем матрицу (matrix) в шейдерную 
            // uniform переменную matrix
            shader.UniformMat4(matrix, "matrix");

            // рисуем треугольник(точнее треугольник)
            vao.draw(TRIANGLE);
            // обратите внимание, что я не передаю кол-во вершин,
            // эта функция может их считать автоматически
```

файл vert.glsl, доработаем шейдер
``` glsl
#version 460 core
// версия glsl(у нас последняя как и openGL)

// подключаем атрибут 0 к вектору pos
layout (location = 0) in vec3 pos;

// подключаем атрибут 1 к вектору color
layout (location = 1) in vec3 color;

// отправляем вектор v_color в фрагментный шейдер
out vec3 v_color;

// создаём unifrom матрицу matrix
uniform mat4 matrix;

// главная функция
void main()
{
    // думаю понятно
    v_color = color;

    // говорим ГПУ что координаты вершины это вектор pos и 1.0
    // почему так? OpenGL использует четыре координаты x, y, z, w
    // w - это маштабирование пока-что оставляем = 1
    // для трансформации координат мы умножаем матрицу на ветор позиции
    gl_Position = matrix * vec4(pos, 1.0);
}
```

если всё сделали как я, то вы увидите тот же четырёхугольник

теперь мы можем поиздеваться на нашем четырёхугольником\
вернёмся в main.cpp
```cpp
            // назначаем нашу шейдерную программу
            shader.use();

            // создаём единичную матрицу matrix
            glm::mat4 matrix = glm::mat4(1.0f);

            // выстраиваем матрицу вращения с помощью glm::rotate()
            // эта функция возвращает mat4 матрицу
            // принимает матрицу которую будем вращать,
            // угол поворота в радианах, я использовал glm::radians(45.0f),
            // она превращает градусы в радианы,
            // и последний аргумент - это vec3 вектор,
            // который говорит по какой(каким) осям вращать
            matrix = glm::rotate(
                matrix,              //матрица
                glm::radians(45.0f), //угол поворота в радианах
                glm::vec3(0, 0, 1)   //по каким осям вращать x, y, z
            ); 

            // отправляем матрицу (matrix) в шейдерную 
            // uniform переменную matrix
            shader.UniformMat4(matrix, "matrix");

            // рисуем треугольник(точнее треугольник)
            vao.draw(TRIANGLE);
            // обратите внимание, что я не передаю кол-во вершин,
            // эта функция может их считать автоматически
```

вы получите
![](png/test_3.png)

файл main.cpp доработаем его
```cpp
            matrix = glm::rotate(
                matrix,              //матрица
                glm::radians((float)core::GetTime() * 20.0f), //угол поворота в радианах
                glm::vec3(1, 0, 1)   //по каким осям вращать x, y, z
            );
```
вы получите
![](png/rotated.gif)

+ [дальше]()
+ [назад](va.md) 
+ [в оглавление](manual.md)
