`apt install pkg-config check valgrind clang-format lcov cmake cppcheck g++`  
`apt install libgtest-dev libtbb-dev qt6-dev-base qt6-tools-dev build-essential libgl1-mesa-dev`  
`apt install doxygen graphviz`
`apt install freeglut3-dev`
`doxygen -g` for generate doxigen file  

[simple doxy](https://eax.me/doxygen/)  
[graph make](https://habr.com/ru/articles/253223/)  
В Doxyfile содержится краткое описание проекта, его версия и подобные вещи. Следующие значения стоит сразу изменить.

- Имя проекта:
PROJECT_NAME           = "Project Name"
- Версия проекта:
PROJECT_NUMBER         = 0.1
- Краткое описание проекта:
PROJECT_BRIEF          = "Yet another NoSQL DBMS"
- Куда писать сгенеренные доки:
OUTPUT_DIRECTORY       = doxygen
- Отключаем LaTeX, так как HTML обычно достаточно:
GENERATE_LATEX         = NO
- Где искать файлы, из которых генерировать документацию — список файлов и директорий через пробел:
883 INPUT                  = src include
- Включаем рекурсивный обход директорий:
RECURSIVE              = YES
EXTRACT_PRIVATE        = YES
2439 UML_LOOK               = YES
2512 CALL_GRAPH             = YES
2524 CALLER_GRAPH           = YES

## doxy commands
- @brief — краткое описание метода или класса;
- @param foo — описание аргумента foo процедуры или метода;
- @return — описание возвращаемого значения;
- @class Foo — описание конкретного класса Foo;
- @file fname — описание конкретного файла;
- @mainpage Title — комментарий содержит текст для титульного листа документации;
- @see Ref — ссылка на связанный класс или метод;
- @throws Foo или @exception Foo — метод бросает исключение Foo;
- @warning — предупреждение. Очень ярко выделяется в документации, трудно не заметить;
- @private — пометить класс или метод, как приватный. Удобно, когда не хочется палить в документации какие-то детали реализации;
- @todo — что-то нужно доделать. Doxygen генерирует отдельную страницу со списком всех @todo;
- @deprecated — помечает класс или метод устаревшим. Как и с @todo, Doxygen генерирует отдельную страницу со списком всех устаревших классов и методов;

## gitlab-runner
- `sudo gitlab-runner register`
- Для регистрации понадобятся URL и токен, которые можно получить на страничке задания на платформе.
- В проекте в настройках выбрать ci/cd и создать при необходимости новый раннер-> выдаст URL&token.
- При регистрации ввесит URL, token, tags-на какие теги будет реагировать раннер, среду исполения(shell, docker).
### Удаление ненужных раннеров
- посмотреть url&token `sudo gitlab-runner list`
- `runner unregister --url https://repos21.21-school.ru --token sdfj;gsirsasdf`
- `runner verify --delete  -u https://repos21.21-school.ru -t sdfj;gsirsasdf`
## dir
- `mkdir -pv {debug,tests,src/model,src/view,src/controller}`
## cppcheck
[cppcheck](https://habr.com/ru/articles/210256/)

## model
- conatain entity of project(calc, credit, debit)
- is observer

## controller
- contain methods to use of model. it must be thin

## view
- contain graphical user interface 
- is subscriber

## from c7-smartCalc
`sudo apt install qtcreator cmake g++`  
`sudo apt install qtbase5-examples qtbase5-dev qtdeclarative5-examples qtdeclarative5-dev`  

## cmake
need thin make and huge cmake
cmake
find_library(cal_lib NAMES s21_calc.a HINTS "${CMAKE_SOURCE_DIR}")

include_directories(GUI img)

uniq_ptr lecture 8
cmake lecture 10 00.04.00, 01.04.35
``` cmake
# macx{
# QT+= core gui openglwidgets
# LIBS+= -framework GLUT -framework OpenGL -framework Cocoa}
# else{
# QT+= core gui opengl
# LIBS+= -lOpenGL -lGLU -lglut
# }
```
## OpenGL
[tutorial freecodecamp.org](https://www.youtube.com/watch?v=45MIykWJ-C4&t=14s)

## TODO
переделать чтение из файла на &istream
синглетон не получился на модели в newtonbe
синглетон не получился на facade в nidorina
drag&drop не получился в wellpetr