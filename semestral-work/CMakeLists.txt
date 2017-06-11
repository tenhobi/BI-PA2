cmake_minimum_required(VERSION 3.7)
project(semestral_work)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/game/cell/Cell.cpp src/game/cell/Cell.hpp src/screen/Screen.cpp src/screen/Screen.hpp src/screen/AboutScreen.cpp src/screen/AboutScreen.hpp src/screen/MenuScreen.cpp src/screen/MenuScreen.hpp src/game/Tower.cpp src/game/Tower.hpp src/game/cell/Wall.cpp src/game/cell/Wall.hpp src/game/cell/Road.cpp src/game/cell/Road.hpp src/game/Monster.cpp src/game/Monster.hpp src/game/Game.cpp src/game/Game.hpp src/game/Map.cpp src/game/Map.hpp src/menu/MenuItem.cpp src/menu/MenuItem.hpp src/menu/MenuRating.cpp src/menu/MenuRating.hpp src/menu/MenuHeading.cpp src/menu/MenuHeading.hpp src/menu/MenuOption.cpp src/menu/MenuOption.hpp src/ColorPairGenerator.cpp src/ColorPairGenerator.hpp src/screen/ExitScreen.cpp src/screen/ExitScreen.hpp src/screen/NewGameScreen.cpp src/screen/NewGameScreen.hpp src/screen/LoadGameScreen.cpp src/screen/LoadGameScreen.hpp src/screen/BackScreen.cpp src/screen/BackScreen.hpp src/menu/Menu.cpp src/menu/Menu.hpp src/Config.hpp src/game/cell/Building.cpp src/game/cell/Building.hpp src/screen/GameScreen.cpp src/screen/GameScreen.hpp src/screen/ErrorScreen.cpp src/screen/ErrorScreen.hpp)
add_executable(semestral_work ${SOURCE_FILES})
