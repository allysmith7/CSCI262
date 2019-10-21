cmake_minimum_required(VERSION 3.10)
project(rwg)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(rwg
        main.cpp
        rwg.cpp
        rwg.h)
