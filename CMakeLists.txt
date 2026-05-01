cmake_minimum_required(VERSION 3.31)
project(audioengine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(audioengine ${SOURCES})

target_link_libraries(audioengine PRIVATE miniaudio)
target_include_directories(audioengine PRIVATE src)