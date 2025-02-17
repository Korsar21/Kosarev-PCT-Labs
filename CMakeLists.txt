cmake_minimum_required(VERSION 3.5.0)
project(CMakePresets.json VERSION 0.1.0 LANGUAGES C CXX)

add_library(CMakePresets.json main.cpp)

include(CTest)
enable_testing()

