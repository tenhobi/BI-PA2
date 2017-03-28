cmake_minimum_required(VERSION 3.6)
project(01)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -pedantic")
set(SOURCE_FILES src/main.cpp src/Bag.cpp src/Bag.h src/xxx/Alpha.cpp src/xxx/Alpha.h src/xxx/yyy/Beta.cpp src/xxx/yyy/Beta.h)
add_executable(01 ${SOURCE_FILES})