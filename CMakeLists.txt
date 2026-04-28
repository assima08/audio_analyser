cmake_minimum_required(VERSION 3.21)
project(audioAnalyser)

set(CMAKE_CXX_STANDARD 14)

add_executable(audioAnalyser
        AudioReader.cpp
        main.cpp)
