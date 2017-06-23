cmake_minimum_required(VERSION 3.6)
project(02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Integer.cpp src/Integer.hpp)
add_executable(02 ${SOURCE_FILES})
