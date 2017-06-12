#include <string>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

#include "../Config.hpp"
#include "../screen/InfoScreen.hpp"
#include "../screen/ErrorScreen.hpp"
#include "cell/Cell.hpp"
#include "cell/Wall.hpp"
#include "cell/Road.hpp"
#include "cell/Building.hpp"
#include "Tower.hpp"

#include "Game.hpp"

// milliseconds
#define GAME_INFO_DELAY 500

// Using in load () method, checks if read from file was success.
#define FILE_READ_CHECK if (inFile.fail()) { errorScreen.process("Read from file has failed."); return false; }

// Using in save () method, checks if write from file was success.
#define FILE_WRITE_CHECK if (outFile.fail()) { errorScreen.process("Write into file has failed."); return false; }

#define GAME_MAX_MONSTERS 5

#define GAME_KILL_MONEY 5
#define GAME_WIN_MONEY 50
#define GAME_ROUND_MONEY 25

Game::Game (bool newGame) : newGame(newGame), map(Map(0, 0)) {}

bool Game::load (std::string fileName) {
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

  infoScreen.process("Tower types loading.", GAME_INFO_DELAY);

  int numberOfTowerTypes;

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

  infoScreen.process("Monster types loading.", GAME_INFO_DELAY);

  int numberOfMonsterTypes;

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

  infoScreen.process("Map loading.", GAME_INFO_DELAY);

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
        case SW_CHAR_WALL:
          map.data[i][j] = new Wall();
          break;
        case SW_CHAR_START:
          if (!hasStartOfRoad) {
            hasStartOfRoad = true;
            map.data[i][j] = new Road(RoadState::START);
            startRoadY = i;
            startRoadX = j;
            startCoords = std::pair<int, int>(startRoadY, startRoadX);
          } else {
            errorScreen.process("Multiple starts of road.");
            return false;
          }
          break;
        case SW_CHAR_END:
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
        case SW_CHAR_CELL:
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

  infoScreen.process("Loading towers in map.", GAME_INFO_DELAY);

  int numberOfTowersInMap;

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

    Tower* tmp = new Tower(towerTypeList[type - 1]);
    tmp->y = leftTopCornerY;
    tmp->x = leftTopCornerX;
    tmp->letter = towerLetter++;

    towersInMap.push_back(
      tmp
    );
  }

  for (int i = 0; i < (int) towersInMap.size(); ++i) {
    for (int j = towersInMap[i]->y; j < towersInMap[i]->y + towersInMap[i]->getHeight(); ++j) {
      for (int k = towersInMap[i]->x; k < towersInMap[i]->x + towersInMap[i]->getWidth(); ++k) {

        delete map.data[j][k];
        map.data[j][k] = new Building(towersInMap[i]);
      }
    }
  }
//
//  int counter = 0;
//
//  for (int i = 0; i < (int) map.data.size(); ++i) {
//    for (int j = 0; j < (int) map.data[i].size(); ++j) {
//      Cell* x = &*map.data[i][j];
//
//      // Cell is Wall
//      if (dynamic_cast<Building*>(x) != NULL) {
//        counter++;
//      }
//    }
//  }

  inFile.close();

  infoScreen.process("Generating closest road from start to end.", GAME_INFO_DELAY);

  return makeRoad(startRoadY, startRoadX, endRoadY, endRoadX);
}

bool Game::save (std::string fileName) {
  InfoScreen infoScreen;
  ErrorScreen errorScreen;

  std::ofstream outFile;

  // trim file name

  while (!fileName.empty() && std::isspace(*fileName.begin())) {
    fileName.erase(fileName.begin());
  }

  while (!fileName.empty() && std::isspace(*fileName.rbegin())) {
    fileName.erase(fileName.length() - 1);
  }

  outFile.open(std::string(SW_GAME_DATA_SAVE) + fileName + ".game");

  if (!outFile.is_open()) {
    return false;
  }

  // Tower types

  outFile << (int) towerTypeList.size() << std::endl << std::endl;

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

  outFile << (int) monsterTypeList.size() << std::endl << std::endl;

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
        outFile << SW_CHAR_WALL;
      }
        // Cell is Road
      else if (dynamic_cast<Road*>(x) != NULL) {
        switch (dynamic_cast<Road*>(x)->getState()) {
          case RoadState::START:
            outFile << SW_CHAR_START;
            break;
          case RoadState::END:
            outFile << SW_CHAR_END;
            break;
          default:
            outFile << SW_CHAR_CELL;
            break;
        }
      } else {
        outFile << SW_CHAR_CELL;
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

  outFile << (int) towersInMap.size() << std::endl << std::endl;

  FILE_WRITE_CHECK

  for (int i = 0; i < (int) towersInMap.size(); ++i) {
    for (int j = 0; j < (int) towerTypeList.size(); ++j) {
      if (*towersInMap[i] == towerTypeList[j]) {
        outFile << j + 1 << std::endl;
        outFile << towersInMap[i]->y << " " << towersInMap[i]->x << std::endl;
        outFile << std::endl;

        FILE_WRITE_CHECK
        break;
      }
    }
  }

  return true;
}

GameState Game::nextRound (WINDOW* gameWindow, WINDOW* statsWindow, WINDOW* towerWindow) {
  InfoScreen infoScreen;
  ErrorScreen errorScreen;
  infoScreen.process("Round " + std::to_string(round));

  int startInvasionCount = invasionCount;

  if (invasionCount >= invasionLimit) {
    infoScreen.process("You have already finished the game.");
    infoScreen.process("Money $" + std::to_string(money) + ", at round " + std::to_string(round));
    return GameState::FINISHED;
  }

  for (int i = 0; i < GAME_MAX_MONSTERS + round; ++i) {
    int min = 0;
    int max = (int) monsterTypeList.size() - 1;
    int type = rand() % (max - min + 1) + min;

    Monster tmp = Monster(monsterTypeList[type]);
    tmp.coords = std::pair<int, int>(startCoords.first, startCoords.second);
    tmp.pathIndex = 0;
    tmp.cellPart = 0;
    monstersInMap.push_back(tmp);
  }

  for (int i = 0; i < (int) towersInMap.size(); ++i) {
    towersInMap[i]->initRound();
  }

  while (!monstersInMap.empty()) {
    std::vector<Monster>::iterator it = monstersInMap.begin();
    while (it != monstersInMap.end()) {
      wclear(gameWindow);
      wclear(statsWindow);
      wclear(towerWindow);
      print(gameWindow, statsWindow, towerWindow, false);
      wrefresh(gameWindow);
      wrefresh(statsWindow);
      wrefresh(towerWindow);

      it->cellPart += it->getSpeed();

      if (it->cellPart >= 1) {
        it->cellPart = 0;
        it->pathIndex++;

        print(gameWindow, statsWindow, towerWindow, false);
        wrefresh(gameWindow);
        wrefresh(statsWindow);
        wrefresh(towerWindow);

        for (int i = 0; i < (int) towersInMap.size(); ++i) {
          if (
            roadList[it->pathIndex].first >= towersInMap[i]->y - towersInMap[i]->getRange() &&

            roadList[it->pathIndex].first <=
            towersInMap[i]->y + towersInMap[i]->getHeight() + towersInMap[i]->getRange() &&

            roadList[it->pathIndex].second >= towersInMap[i]->x - towersInMap[i]->getRange() &&

            roadList[it->pathIndex].second <=
            towersInMap[i]->x + towersInMap[i]->getWidth() + towersInMap[i]->getRange()
            ) {
            if (towersInMap[i]->currentAmmo == -1) {
              it->attack(towersInMap[i]->getAttackPower());
            }

            if (towersInMap[i]->currentAmmo > 0) {
              it->attack(towersInMap[i]->getAttackPower());
              --towersInMap[i]->currentAmmo;
            }
          }
        }

        if (it->getHealth() <= 0) {
          monstersInMap.erase(it);
          money += GAME_KILL_MONEY;
          puts("\a");
        } else if (it->pathIndex == (int) roadList.size() - 1) {
          monstersInMap.erase(it);
          invasionCount++;

          if (monstersInMap.empty()) {
            break;
          }
        } else {
          ++it;
        }
      } else {
        ++it;
      }
    }

    // milliseconds
    timeout(100);
    getch();
  }

  round++;

  if (startInvasionCount == invasionCount) {
    money += GAME_WIN_MONEY;
  }

  if (invasionCount < invasionLimit) {
    money += GAME_ROUND_MONEY;
    return GameState::IN_PROGRESS;
  }

  infoScreen.process("You have lost the game, sorry. Monsters invaded your kingdom.");
  infoScreen.process("Money $" + std::to_string(money) + ", at round " + std::to_string(round));
  return GameState::LOST;
}

GameState Game::print (WINDOW* gameWindow, WINDOW* statsWindow, WINDOW* towersWindow) {
  return print(gameWindow, statsWindow, towersWindow, false);
}

GameState Game::print (WINDOW* gameWindow, WINDOW* statsWindow, WINDOW* towersWindow, bool showRoad) {
  // game window print

  for (int i = 0; i < map.height; ++i) {
    for (int j = 0; j < map.width; ++j) {
      Cell* x = &*map.data[i][j];

      // Cell is Building
      if (dynamic_cast<Building*>(x) != NULL) {
        mvwprintw(gameWindow, i, j, std::string(1, dynamic_cast<Building*>(x)->getTower()->letter).c_str());
      }
        // Cell is Wall
      else if (dynamic_cast<Wall*>(x) != NULL) {
        mvwprintw(gameWindow, i, j, std::string(1, SW_CHAR_WALL).c_str());
      }
        // Cell is Road
      else if (dynamic_cast<Road*>(x) != NULL) {
        if (dynamic_cast<Road*>(x)->getState() == RoadState::START) {
          mvwprintw(gameWindow, i, j, std::string(1, SW_CHAR_START).c_str());
        } else if (dynamic_cast<Road*>(x)->getState() == RoadState::END) {
          mvwprintw(gameWindow, i, j, std::string(1, SW_CHAR_END).c_str());
        } else {
          if (showRoad) {
            mvwprintw(gameWindow, i, j, std::string(1, SW_CHAR_ROAD).c_str());
          } else {
            for (int k = 0; k < (int) monstersInMap.size(); ++k) {
              mvwprintw(gameWindow, roadList[monstersInMap[k].pathIndex].first,
                        roadList[monstersInMap[k].pathIndex].second, std::string(1, SW_CHAR_MONSTER).c_str());
            }
          }
        }
      }
        // Cell is regular Cell
      else {
        mvwprintw(gameWindow, i, j, std::string(1, SW_CHAR_CELL).c_str());
      }
    }
  }

  wrefresh(gameWindow);

  // stats window print

  wclear(statsWindow);

  mvwprintw(statsWindow, 0, 0, std::string("Round: " + std::to_string(round)).c_str());
  mvwprintw(statsWindow, 1, 0, std::string("Monsters alive: " + std::to_string((int) monstersInMap.size())).c_str());
  mvwprintw(statsWindow, 2, 0, std::string("Money: " + std::to_string(money)).c_str());
  mvwprintw(statsWindow, 3, 0,
            std::string("Invasion: " + std::to_string(invasionCount) + "/" + std::to_string(invasionLimit)).c_str());

  wrefresh(statsWindow);

  // towers window print

  mvwprintw(towersWindow, 0, 0,
            std::string("Towers types: " + std::to_string((int) towerTypeList.size()) + " | Towers in map: " +
                        std::to_string((int) towersInMap.size())).c_str());

  for (int i = 0; i < (int) towerTypeList.size(); ++i) {
    mvwprintw(towersWindow, i + 1, 0, std::string(
      std::to_string(i) + ": $" + std::to_string(towerTypeList[i].getCost()) + ", " +
      std::to_string(towerTypeList[i].getHeight()) + "x" + std::to_string(towerTypeList[i].getWidth()) + ", ! " +
      std::to_string(towerTypeList[i].getAttackPower()) + ", o " + std::to_string(towerTypeList[i].getRange()) +
      ", :: " + std::to_string(towerTypeList[i].getAmmoPerRound())).c_str());
  }

  wrefresh(towersWindow);

  return GameState::IN_PROGRESS;
}

bool Game::makeRoad (int startRoadY, int startRoadX, int endRoadY, int endRoadX) {
  ErrorScreen errorScreen;
  InfoScreen infoScreen;

  std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>> mapCells;
  mapCells.resize((unsigned long) map.height,
                  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>((unsigned long) map.width));

  // define default values
  for (int i = 0; i < (int) mapCells.size(); ++i) {
    for (int j = 0; j < (int) mapCells[i].size(); ++j) {
      mapCells[i][j].first = std::pair<int, int>(i, j);
      mapCells[i][j].second = std::pair<int, int>(-1, -1);
    }
  }

  std::queue<std::pair<int, int>> mapQueue;

  // put the end of map to the queue
  mapQueue.push(std::pair<int, int>(endRoadY, endRoadX));

  bfs(mapCells, mapQueue);

  int posY = startRoadY;
  int posX = startRoadX;

  // generates route path list

  while (true) {
//    infoScreen.process(std::to_string(posY) + "; " + std::to_string(posX));

    if (posY == -1 || posX == -1) {
      return false;
    }

    if (mapCells[posY][posX].second.first == -1 || mapCells[posY][posX].second.second == -1) {
      Cell* x = &*map.data[posY][posX];

      if (dynamic_cast<Road*>(x) != NULL) {
        if (dynamic_cast<Road*>(x)->getState() == RoadState::END) {
          roadList.push_back(std::pair<int, int>(posY, posX));
          return true;
        }
      }

      errorScreen.process("Route can not be build. " + std::to_string(posY) + "; " + std::to_string(posX));
      return false;
    }

    Cell* x = &*map.data[posY][posX];

    if (dynamic_cast<Road*>(x) != NULL) {
      if (dynamic_cast<Road*>(x)->getState() == RoadState::END) {
        roadList.push_back(std::pair<int, int>(posY, posX));
        return true;
      } else if (dynamic_cast<Road*>(x)->getState() == RoadState::START) {
        roadList.push_back(std::pair<int, int>(posY, posX));
      }

      dynamic_cast<Road*>(x)->next = std::pair<int, int>(mapCells[posY][posX].second.first,
                                                         mapCells[posY][posX].second.second);
      posY = mapCells[posY][posX].second.first;
      posX = mapCells[posY][posX].second.second;

      if (posY == -1 || posX == -1) {
        break;
      }
      continue;
    }

    delete map.data[posY][posX];
    Road* tmp = new Road(RoadState::NORMAL);
    tmp->next = std::pair<int, int>(mapCells[posY][posX].second.first, mapCells[posY][posX].second.second);
    map.data[posY][posX] = tmp;

    roadList.push_back(std::pair<int, int>(posY, posX));

    posY = mapCells[posY][posX].second.first;
    posX = mapCells[posY][posX].second.second;

    if (posY == -1 || posX == -1) {
      break;
    }
  }

  return true;
}

void Game::bfs (std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>& mapCells,
                std::queue<std::pair<int, int>>& mapQueue) {
  for (int i = 0; i < (int) mapQueue.size(); ++i) {
    std::pair<int, int>& node = mapQueue.front();

    if ((node.second + 1) < (int) mapCells[0].size()) {
      if (mapCells[node.first][node.second + 1].second.first == -1 &&
          mapCells[node.first][node.second + 1].second.second == -1) {

        Cell* x = &*map.data[node.first][node.second + 1];
        if (map.data[node.first][node.second + 1]->isEmpty() ||
            (dynamic_cast<Road*>(x) != NULL && dynamic_cast<Road*>(x)->getState() == RoadState::START)) {

          // set reference to this node
          mapCells[node.first][node.second + 1].second.first = node.first;
          mapCells[node.first][node.second + 1].second.second = node.second;

          // add to queue
          mapQueue.push(std::pair<int, int>(node.first, node.second + 1));
        }
      }
    }

    if (node.second - 1 >= 0) {
      if (mapCells[node.first][node.second - 1].second.first == -1 &&
          mapCells[node.first][node.second - 1].second.second == -1) {

        Cell* x = &*map.data[node.first][node.second - 1];
        if (map.data[node.first][node.second - 1]->isEmpty() ||
            (dynamic_cast<Road*>(x) != NULL && dynamic_cast<Road*>(x)->getState() == RoadState::START)) {

          // set reference to this node
          mapCells[node.first][node.second - 1].second.first = node.first;
          mapCells[node.first][node.second - 1].second.second = node.second;

          // add to queue
          mapQueue.push(std::pair<int, int>(node.first, node.second - 1));
        }
      }
    }

    if ((node.first + 1) < (int) mapCells.size()) {
      if (mapCells[node.first + 1][node.second].second.first == -1 &&
          mapCells[node.first + 1][node.second].second.second == -1) {

        Cell* x = &*map.data[node.first + 1][node.second];
        if (map.data[node.first + 1][node.second]->isEmpty() ||
            (dynamic_cast<Road*>(x) != NULL && dynamic_cast<Road*>(x)->getState() == RoadState::START)) {

          // set reference to this node
          mapCells[node.first + 1][node.second].second.first = node.first;
          mapCells[node.first + 1][node.second].second.second = node.second;

          // add to queue
          mapQueue.push(std::pair<int, int>(node.first + 1, node.second));
        }
      }
    }

    if ((node.first - 1) >= 0) {
      if (mapCells[node.first - 1][node.second].second.first == -1 &&
          mapCells[node.first - 1][node.second].second.second == -1) {
        Cell* x = &*map.data[node.first - 1][node.second];
        if (map.data[node.first - 1][node.second]->isEmpty() ||
            (dynamic_cast<Road*>(x) != NULL && dynamic_cast<Road*>(x)->getState() == RoadState::START)) {

          // set reference to this node
          mapCells[node.first - 1][node.second].second.first = node.first;
          mapCells[node.first - 1][node.second].second.second = node.second;

          // add to queue
          mapQueue.push(std::pair<int, int>(node.first - 1, node.second));
        }
      }
    }

    mapQueue.pop();
  }

  if (!mapQueue.empty()) {
    bfs(mapCells, mapQueue);
  }
}

int Game::getMapHeight () {
  return map.height;
}

int Game::getMapWidth () {
  return map.width;
}

Game::~Game () {
  for (int i = 0; i < (int) towersInMap.size(); ++i) {
    delete towersInMap[i];
  }
}

int Game::getNumberOfTowerTypes () {
  return (int) towerTypeList.size();
}

bool Game::addTower (int type, int y, int x) {
  ErrorScreen errorScreen;

  if (type >= (int) towerTypeList.size() || type < 0) {
    errorScreen.process("Not existed type of tower used.");
    return false;
  }

  if (y < 0 || y >= map.height || x < 0 || x >= map.width) {
    errorScreen.process("Coordinates are wrong.");
    return false;
  }

  if (towerTypeList[type].getCost() > money) {
    errorScreen.process("Tower is too much expensive.");
    return false;
  }

  for (int j = y; j < y + towerTypeList[type].getHeight(); ++j) {
    for (int k = x; k < x + towerTypeList[type].getWidth(); ++k) {
      if (!map.data[j][k]->isEmpty()) {
        errorScreen.process("Tower cannot be created on not empty cell.");
        return false;
      }
    }
  }

  Tower* tmp = new Tower(towerTypeList[type]);
  tmp->y = y;
  tmp->x = x;
  tmp->letter = towerLetter++;

  towersInMap.push_back(
    tmp
  );

  for (int i = 0; i < (int) towersInMap.size(); ++i) {
    for (int j = towersInMap[i]->y; j < towersInMap[i]->y + towersInMap[i]->getHeight(); ++j) {
      for (int k = towersInMap[i]->x; k < towersInMap[i]->x + towersInMap[i]->getWidth(); ++k) {

        delete map.data[j][k];
        map.data[j][k] = new Building(towersInMap[i]);
      }
    }
  }

  money -= towerTypeList[type].getCost();

  return true;
}
