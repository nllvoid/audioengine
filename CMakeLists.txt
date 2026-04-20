cmake_minimum_required(VERSION 3.31)
project(oscillator)

set(CMAKE_CXX_STANDARD 20)

add_executable(oscillator src/main.cpp
        vendor/miniaudio.h
        src/Oscillator.cpp
        src/Oscillator.h
        src/AudioPlayer.h
        src/AudioPlayer.cpp
        src/AudioEffect.h
        src/effects/LowPassFilter.h
        src/effects/LowPassFilter.cpp
        src/effects/HighPassFilter.h
        src/effects/HighPassFilter.cpp
        src/effects/HardClipping.h
        src/effects/HardClipping.cpp
        src/effects/SoftClipping.h
        src/effects/SoftClipping.cpp
        src/effects/Delay.h
        src/effects/Delay.cpp
        src/Notes.h
        src/Arpeggiator.h
        src/Arpeggiator.cpp)
