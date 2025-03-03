cmake_minimum_required(VERSION 3.10)
project(PlanetSystem)

set(CMAKE_CXX_STANDARD 17)

add_library(planet STATIC planet.cpp)

add_executable(main main.cpp)

target_link_libraries(main planet)
