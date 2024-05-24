# Copyright 16.12.2022  s21genesiss@gmail.com
# Version 0.2
# Скрипт для установки программ для разработки.

#!/bin/bash

USER=$(whoami)

echo "Hello $USER."

echo "Обновление системы."
sudo apt update & upgrade -y
echo "Установка gcc make perl."
sudo apt install gcc make perl -y
echo "Установка отладчика GNU и коллекции компиляторов."
sudo apt install build-essential -y
echo "Установка cmake."
sudo apt install cmake -y
sudo snap install cmake
echo "Установка valgrind."
sudo apt install valgrind
echo "Установка OpenGL."
sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev mesa-utils
echo "Версия OpenGL:"
glxinfo | grep "OpenGL core profile version string"
echo "Установка утилит для OpenGL."
sudo apt install mesa-utils
echo "Установка texinfo."
sudo apt-get install texinfo -y
echo "Установка библиотеки GLFW"
sudo apt install libglfw3
sudo apt install libglfw3-dev
echo "Установка xdg-utils для установки программы, которая открывает файлы или ссылки в предпочтительной программе."
sudo apt install xdg-utils
echo "Установка инструмент для форматирования кода С/С++ clang-format-11."
sudo apt-get install clang-format-11 -y
echo "Установка Qt6.02."
sudo apt update -y
sudo apt install qtcreator -y
echo "Установка примеров программ для Qt."
sudo apt install qtbase5-examples qtdeclarative5-examples qtbase5-doc-html -y
echo "Установка инструментов разработки для Qt."
sudo apt install qtbase5-dev qtwayland5-dev-tools qtwayland5 -y
echo "Установить пакеты mesa-common-dev, libgl1-mesa-dev и libglu1. -mesa-dev."
sudo apt install libglfw3-dev libglm-dev libepoxy-dev libboost-all-dev libglew-dev libopenal-dev libalut-dev
echo "Завершение установки."

#echo "Удаление Qt Creator."
#sudo apt-get remove qt5-default qtcreator
