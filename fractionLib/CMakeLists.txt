cmake_minimum_required(VERSION 3.10)
project(fractionLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fraction STATIC
    Fraction.cpp
)

target_include_directories(fraction PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
