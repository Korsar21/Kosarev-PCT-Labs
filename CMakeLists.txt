cmake_minimum_required(VERSION 3.10)
project(lab_1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(mymath)
add_subdirectory(mymath2)

add_executable(lab_1 main.cpp)

target_link_libraries(lab_1 mymath mymath2)
