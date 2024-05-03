cmake_minimum_required(VERSION 3.27)
project(Scrabble_projekt_C_)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
include_directories(include/project)

add_library(DAWG ../DAWG/Dawg.cpp)

add_executable(Scrabble_projekt_C_
        include/project/Ruut.h
        src/Ruut.cpp
        include/project/Scrabble.h
        src/Scrabble.cpp
        include/project/Laud.h
        src/Laud.cpp
        include/project/Nupp.h
        src/Nupp.cpp
        include/project/Mang.h
        src/Mang.cpp
        include/project/Kott.h
        src/Kott.cpp
        include/project/Kuna.h
        src/Kuna.cpp
)

target_link_libraries(Scrabble_projekt_C_ PRIVATE DAWG)

