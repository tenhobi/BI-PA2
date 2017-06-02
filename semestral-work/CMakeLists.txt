cmake_minimum_required(VERSION 3.7)
project(semestral_work)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/game/cell/Cell.cpp src/game/cell/Cell.hpp src/screen/Screen.cpp src/screen/Screen.hpp src/screen/AboutScreen.cpp src/screen/AboutScreen.hpp src/screen/MenuScreen.cpp src/screen/MenuScreen.hpp src/game/cell/Tower.cpp src/game/cell/Tower.hpp src/game/cell/Wall.cpp src/game/cell/Wall.hpp src/game/cell/Road.cpp src/game/cell/Road.hpp src/game/entity/Entity.cpp src/game/entity/Entity.hpp src/game/entity/Zombie.cpp src/game/entity/Zombie.hpp src/game/entity/Soldier.cpp src/game/entity/Soldier.hpp src/game/entity/Alien.cpp src/game/entity/Alien.hpp src/game/Game.cpp src/game/Game.hpp src/game/Map.cpp src/game/Map.hpp)
add_executable(semestral_work ${SOURCE_FILES})
