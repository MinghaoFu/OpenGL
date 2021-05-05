cmake_minimum_required(VERSION 3.17)
project(opengl_shader)

set(CMAKE_CXX_STANDARD 14)
find_library(SOIL.lib)

add_executable(opengl_shader main.cpp)