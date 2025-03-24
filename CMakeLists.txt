# CMakeLists.txt (корневой)
cmake_minimum_required(VERSION 3.10)
project(FractionProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем библиотеку из подкаталога
add_subdirectory(fractionLib)

# Создаем исполняемый файл из main.cpp
add_executable(FractionApp
    main.cpp
)

# Связываем исполняемый файл с библиотекой
target_link_libraries(FractionApp fraction)
