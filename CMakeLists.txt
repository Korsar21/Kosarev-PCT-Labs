cmake_minimum_required(VERSION 3.10)
project(FractionProject)

# Повышаем стандарт до C++17 для поддержки всех возможностей
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем подпроект с библиотекой
add_subdirectory(fractionLib)

# Создаем исполняемый файл
add_executable(fraction_app main.cpp)

# Связываем с библиотекой и добавляем пути к заголовочным файлам
target_link_libraries(fraction_app PRIVATE fraction)
target_include_directories(fraction_app PRIVATE ${CMAKE_SOURCE_DIR}/fractionLib)
