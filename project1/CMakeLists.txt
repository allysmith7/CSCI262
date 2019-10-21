cmake_minimum_required(VERSION 3.14)
project(project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project1
        cmake-build-debug/analysis.txt
        personality_test.cpp
        personality_test.h
        proj1.cpp
        cmake-build-debug/questions.txt)
