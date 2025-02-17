cmake_minimum_required(VERSION 3.23)
project(lab_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_1 main.cpp)

IF (NOT WIN32)
target_link_libraries(lab_1 m)
ENDIF()
