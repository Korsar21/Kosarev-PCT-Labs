cmake_minimum_required(VERSION 3.23)

set(project "lab7")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main.cpp)

add_subdirectory(PrintedEdition)
add_subdirectory(MyVector)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})


        add_library(MyVector STATIC
    MyVector/MyStack.cpp
    MyVector/MyVector.cpp
)

target_link_libraries(${project} PrintedEdition MyVector)
# target_link_libraries(lab7 PrintedEdition MyVector)
# target_link_libraries(${project} MyVector)
