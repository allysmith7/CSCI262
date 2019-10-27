cmake_minimum_required(VERSION 3.14)
project(code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
    brute_model.cpp
    brute_model.h
    main.cpp
    map_model.cpp
    map_model.h
    markov.cpp
    markov.h
    model.h
    word_model.cpp
    word_model.h)
