cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(code
        main.cpp
        maze_solver.cpp
        maze_solver.h)
