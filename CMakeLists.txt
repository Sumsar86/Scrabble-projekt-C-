cmake_minimum_required(VERSION 3.27)
project(Scrabble_projekt_C_)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/project)

add_executable(Scrabble_projekt_C_
        build/test.txt
        include/project/Ruut.h
        include/project/Scrabble.h
        src/Ruut.cpp
        src/Scrabble.cpp)
