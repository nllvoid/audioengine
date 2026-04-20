cmake_minimum_required(VERSION 3.31)
project(oscillator)

set(CMAKE_CXX_STANDARD 20)

add_executable(oscillator src/main.cpp
        vendor/miniaudio.h
        src/Oscillator.cpp
        src/Oscillator.h
        src/AudioPlayer.h
        src/AudioPlayer.cpp)
