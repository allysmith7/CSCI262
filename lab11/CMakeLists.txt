cmake_minimum_required(VERSION 3.14)
project(lab11)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab11 Queue.h tests.cpp Queue.cpp)