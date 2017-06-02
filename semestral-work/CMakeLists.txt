cmake_minimum_required(VERSION 3.7)
project(semestral_work)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/cell/Cell.cpp src/cell/Cell.hpp src/screen/Screen.cpp src/screen/Screen.hpp src/screen/AboutScreen.cpp src/screen/AboutScreen.hpp src/screen/MenuScreen.cpp src/screen/MenuScreen.hpp src/cell/Tower.cpp src/cell/Tower.hpp src/cell/Wall.cpp src/cell/Wall.hpp src/cell/Road.cpp src/cell/Road.hpp src/entity/Entity.cpp src/entity/Entity.hpp src/entity/Zombie.cpp src/entity/Zombie.hpp src/entity/Soldier.cpp src/entity/Soldier.hpp src/entity/Alien.cpp src/entity/Alien.hpp)
add_executable(semestral_work ${SOURCE_FILES})
