cmake_minimum_required(VERSION 4.3)
project(marie)

set(CMAKE_CXX_STANDARD 20)

add_executable(marie main.cpp
        classes/MarieCPU.cpp
        classes/MarieCPU.h)
