# fractionLib/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(fractionLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем статическую библиотеку из Fraction.cpp
add_library(fraction STATIC
    Fraction.cpp
)

# Экспортируем интерфейс библиотеки
target_include_directories(fraction PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
