cmake_minimum_required(VERSION 3.14)
project(lab12)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab12
        tests.cpp
        unix_clock.cpp
        unix_clock.h
        analog_clock.h)
