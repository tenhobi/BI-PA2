#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "../screen/InfoScreen.hpp"
#include "../screen/ErrorScreen.hpp"
#include "cell/Cell.hpp"
#include "cell/Wall.hpp"
#include "cell/Road.hpp"
#include "Tower.hpp"

#include "Game.hpp"

// milliseconds
#define GAME_INFO_DELAY 500

// Using in load () method, checks if read from file was success.
#define FILE_READ_CHECK if (inFile.fail()) { errorScreen.process("Read from file has failed."); return false; }

// Using in save () method, checks if write from file was success.
#define FILE_WRITE_CHECK if (outFile.fail()) { errorScreen.process("Write into file has failed."); return false; }

Game::Game (std::string fileName, bool newGame) : fileName(fileName), newGame(newGame), map(Map(0, 0)) {}

bool Game::load () {
  InfoScreen infoScreen;
  ErrorScreen errorScreen;

  std::ifstream inFile;

  if (newGame) {
    inFile.open(std::string(SW_GAME_DATA_TEMPLATE) + fileName);
  } else {
    inFile.open(std::string(SW_GAME_DATA_SAVE) + fileName);
  }

  if (!inFile.is_open()) {
    return false;
  }

  infoScreen.process("Tower types loading", GAME_INFO_DELAY);

  inFile >> numberOfTowerTypes;

  FILE_READ_CHECK

  for (int i = 0; i < numberOfTowerTypes; ++i) {
    int cost, height, width, attackPower, range, ammoPerRound;

    inFile >> cost >> height >> width >> attackPower >> range >> ammoPerRound;

    FILE_READ_CHECK

    towerTypeList.push_back(
      Tower(cost, height, width, attackPower, range, ammoPerRound)
    );
  }

  infoScreen.process("Monster types loading", GAME_INFO_DELAY);

  inFile >> numberOfMonsterTypes;

  FILE_READ_CHECK

  for (int i = 0; i < numberOfMonsterTypes; ++i) {
    int health, armor;
    float speed;

    inFile >> health >> speed >> armor;

    FILE_READ_CHECK

    monsterTypeList.push_back(
      Monster(health, speed, armor)
    );
  }

  infoScreen.process("Map loading", GAME_INFO_DELAY);

  inFile >> map.height >> map.width;

  FILE_READ_CHECK

  map.resize();

  bool hasStartOfRoad = false;
  int startRoadY = -1;
  int startRoadX = -1;

  bool hasEndOfRoad = false;
  int endRoadY = -1;
  int endRoadX = -1;

  for (int i = 0; i < map.height; ++i) {
    for (int j = 0; j < map.width; ++j) {
      char input;

      input = (char) inFile.get();

      FILE_READ_CHECK

      switch (input) {
        case '\n':
          j--;
          break;
        case '#':
          map.data[i][j] = new Wall();
          break;
        case '-':
          if (!hasStartOfRoad) {
            hasStartOfRoad = true;
            map.data[i][j] = new Road(RoadState::START);
            startRoadY = i;
            startRoadX = j;
          } else {
            errorScreen.process("Multiple starts of road.");
            return false;
          }
          break;
        case '=':
          if (!hasEndOfRoad) {
            hasEndOfRoad = true;
            map.data[i][j] = new Road(RoadState::END);
            endRoadY = i;
            endRoadX = j;
          } else {
            errorScreen.process("Multiple ends of road.");
            return false;
          }
          break;
        case ' ':
          map.data[i][j] = new Cell();
          break;
        default:
          errorScreen.process("Wrong input character in map data.");
          return false;
      }

    }
  }

  if (!hasEndOfRoad || !hasStartOfRoad) {
    errorScreen.process("Game map does no contain a start or an end cell.");
    return false;
  }

  inFile >> round >> money >> invasionLimit >> invasionCount;

  FILE_READ_CHECK

  infoScreen.process("Loading towers in map", GAME_INFO_DELAY);

  inFile >> numberOfTowersInMap;

  FILE_READ_CHECK

  for (int i = 0; i < numberOfTowersInMap; ++i) {
    int type, leftTopCornerY, leftTopCornerX;

    inFile >> type >> leftTopCornerY >> leftTopCornerX;

    FILE_READ_CHECK

    if (type > (int) towerTypeList.size() || type <= 0) {
      errorScreen.process("Not existed type of tower used.");
      return false;
    }

    for (int j = leftTopCornerY; j < leftTopCornerY + towerTypeList[type - 1].getHeight(); ++j) {
      for (int k = leftTopCornerX; k < leftTopCornerX + towerTypeList[type - 1].getWidth(); ++k) {
        if (!map.data[j][k]->isEmpty()) {
          errorScreen.process("Tower cannot be created on not empty cell.");
          return false;
        }
      }
    }

    Tower tmp = towerTypeList[type - 1];
    tmp.y = leftTopCornerY;
    tmp.x = leftTopCornerX;

    towersInMap.push_back(
      tmp
    );
  }

  inFile.close();

  infoScreen.process("Generating closest road from start to end", GAME_INFO_DELAY);

  makeRoad(startRoadY, startRoadX, endRoadY, endRoadX);

  return true;
}

bool Game::save () {
  InfoScreen infoScreen;
  ErrorScreen errorScreen;

  std::ofstream outFile;

  // TODO: name of file
  std::string outputName = "muj-super-soubor";

  outFile.open(std::string(SW_GAME_DATA_SAVE) + outputName + ".game");

  if (!outFile.is_open()) {
    return false;
  }

  // Tower types

  outFile << numberOfTowerTypes << std::endl << std::endl;

  FILE_WRITE_CHECK

  for (int i = 0; i < (int) towerTypeList.size(); ++i) {
    outFile << towerTypeList[i].getCost() << std::endl;
    outFile << towerTypeList[i].getHeight() << " " << towerTypeList[i].getWidth() << std::endl;
    outFile << towerTypeList[i].getAttackPower() << std::endl;
    outFile << towerTypeList[i].getRange() << std::endl;
    outFile << towerTypeList[i].getAmmoPerRound() << std::endl;

    outFile << std::endl;

    FILE_WRITE_CHECK
  }

  outFile << std::endl << std::endl;

  // Monsters type

  outFile << numberOfMonsterTypes << std::endl << std::endl;

  FILE_WRITE_CHECK

  for (int i = 0; i < (int) monsterTypeList.size(); ++i) {
    outFile << monsterTypeList[i].getHealth() << std::endl;
    outFile << monsterTypeList[i].getSpeed() << std::endl;
    outFile << monsterTypeList[i].getArmor() << std::endl;

    outFile << std::endl;
  }

  FILE_WRITE_CHECK

  outFile << std::endl << std::endl;

  // Map

  outFile << map.height << " " << map.width << std::endl;

  FILE_WRITE_CHECK

  outFile << std::endl;

  for (int i = 0; i < map.height; ++i) {
    for (int j = 0; j < map.width; ++j) {
      Cell* x = &*map.data[i][j];

      // Cell is Wall
      if (dynamic_cast<Wall*>(x) != NULL) {
        outFile << "#";
      }
      // Cell is Road
      else if (dynamic_cast<Road*>(x) != NULL) {
        switch (dynamic_cast<Road*>(x)->getState()) {
          case RoadState::START:
            outFile << "-";
            break;
          case RoadState::END:
            outFile << "=";
            break;
          default:
            break;
        }
      } else {
        outFile << " ";
      }

      FILE_WRITE_CHECK
    }
    outFile << std::endl;
  }

  outFile << std::endl;

  // Towers in map

  outFile << round << std::endl << std::endl;
  outFile << money << std::endl << std::endl;
  outFile << invasionLimit << std::endl << std::endl;
  outFile << invasionCount << std::endl << std::endl;

  outFile << numberOfTowersInMap << std::endl << std::endl;

  FILE_WRITE_CHECK

  for (int i = 0; i < (int) towersInMap.size(); ++i) {
    for (int j = 0; j < (int) towerTypeList.size(); ++j) {
      if (towersInMap[i] == towerTypeList[j]) {
        outFile << j + 1 << std::endl;
        outFile << towersInMap[i].y << " " << towersInMap[i].x << std::endl;
        outFile << std::endl;

        FILE_WRITE_CHECK
        break;
      }
    }
  }

  return true;
}

void Game::start () {
  InfoScreen infoScreen;
  infoScreen.process("Game started");

  loop();
}

void Game::loop () {
  InfoScreen infoScreen;
  infoScreen.process("Round");
}

void Game::print () {

}

void Game::makeRoad (int startRoadY, int startRoadX, int endRoadY, int endRoadX) {

}
