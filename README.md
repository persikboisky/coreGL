## Инструкция
```sh
1. скачиваем и разархивируем архив
2. открываем проект файл openGL.sln (должна быть установлена Visual Studio)
3. проверяем что бы сверху стояло Reales x64 (если не стоит, то устанавливаем)
4. запускаем (Вы увидите спрайт с логотипом ядра)
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
> Чтобы указать другую версию openGL заходим в файл core.h (src/core/core.h)
> Находим эти строки (они в начале), и указываем версию
> #define VERSION_MAJOR первое число
> #define VERSION_MINOR второе число
> ```

## Системы ядра
>[!NOTE]
>```sh
> в папке src/core расположены все системы и под системы ядра
> в файле src/main.cpp написан демонстрационный код
> По сути ядро находится в файле core и подключается заголовочным файлом core.h
> Некоторые функции могут вызывать исключения, я ниже опишу значение всех исключений(вызвать их почти невозможно:))
>```

## Содержание ядра
```sh
1.window (отвечает за создание и взаимодействие окна)
2.graphics (хз что писать:) )
3.loaders (Загрузка файлов)
4.util (Различный алгоритмы для упрощения жизни)
```

## Система window
```sh
Window(const char* title, int width, int height) конструктор создания окна(окон)
Принимает заголовок, высоту окна, ширину окна

Далее все методы рассматриваются относительно созданного вами объекта окна

~Window() - деструктор удаляет окно
width, height - эти переменые хранят текущий размер окна
swapBuffers() - сменяет буфер окна
setSizeBuffer(int width, int height) - Устанавливает размер буфера
setIcon(const char* path) - Устанавливает png иконку для окна
close() - вызывает закрытие окна, но не удаляет его
setContext() - подключает openGL к окну

event->update() - обновляет список эвентов
event->close() - проверяет эвент закрытия окна (тип функции bool)
event->GetMouseLeftButton() - возвращает состояние ЛКМ (тип функции bool)
event->GetMouseRightButton() - возвращает состояние ПКМ (тип функции bool)
event->getKey(int keyCode) - возвращает состояние клавиш (тип функции bool)
принимает номер клавиши

cursor->setCursorMode(int mode) - устанавливает режим курсора
принимает номер режима
cursor->showCursor(bool flag) - делает курсор невидимым
принимает флаг
cursor->disableCursor(bool flag) - выключает курсор
принимает флаг
cursor->setPosition(double x, double y) - устанавливает курсор на указаных координатах
принимает координаты
cursor->getCordCursorX() - возвращает координаты курсора по оси X (тип функции double)
cursor->getCordCursorY() - возвращает координаты курсора по оси Y (тип функции double)
cursor->getCordCursor(double& x, double& y) - передаёт координаты курсора в переменые
принимает переменные для хранения координат
```

## Система graphics
```sh
vao::create(create(float vert[], int sizeOfFloat) создаёт вершиный буфер
принимает массив вершин и размер массивы в байтах
возвращает дескриптор(unsigned int)

vao::addAttribute(unsigned int id, int index, int n, int size, int indentation) добавляет вершины атрибут
принимает дескриптор vao,
индекс атрибута,
количество элементов в атрибуте,
количество элементов на всю вершину,
отступ массиве элементов

vao::Delete(unsigned int id) удаляет vao
принимает дескриптор vao

vao::DeleteALL() удаляет все vao

vao::draw(primitive Primitive, unsigned int id, int first_vert, int count_vert) отрисовывает примитив

shader::createFromCode(const char* codeVert, const char* codeFrag) создаёт шейдер
```












