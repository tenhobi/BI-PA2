#ifndef SEMESTRAL_WORK_GAME_HPP
#define SEMESTRAL_WORK_GAME_HPP

#include <string>
#include <queue>
#include <vector>
#include <ncurses.h>

#include "Tower.hpp"
#include "Monster.hpp"
#include "Map.hpp"

enum GameState {
  FINISHED,
  WIN,
  LOST,
  IN_PROGRESS
};

/**
 * A main class for the tower defense game, which process all initialization, saving, looping etc.
 */
class Game {
public:
  /**
   * A constructor.
   */
  Game (bool newGame);

  ~Game ();

  /**
   * Loads the game from a file.
   *
   * @return success
   */
  bool load (std::string fileName);

  /**
   * Saves the game to a file.
   *
   * @return success
   */
  bool save (std::string fileName);

  /**
   * Process next round of the game.
   */
  GameState nextRound (WINDOW* game, WINDOW* stats);

  GameState print (WINDOW* gameWindow, WINDOW* statsWindow);

  int getMapHeight ();

  int getMapWidth ();

protected:
  bool newGame;

  /**
   * Map data.
   */
  Map map;

  /**
   * Money ammount.
   */
  int money;

  /**
   * Round number.
   */
  int round;

  /**
   * Limit of monster invasion.
   */
  int invasionLimit;

  /**
   * Current number of invaded monsters.
   */
  int invasionCount;

  /**
   * Determines if the game has been changed since the last save.
   */
  bool saved = false;

  /**
   * Determines if the game is finished.
   */
  bool finished;

  int numberOfTowerTypes;

  std::vector<Tower> towerTypeList;

  int numberOfMonsterTypes;

  std::vector<Monster> monsterTypeList;

  int numberOfTowersInMap;

  std::vector<Tower*> towersInMap;

  int towerLetter = 'A';

  void bfs (std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>& mapCells, std::queue<std::pair<int, int>>& mapQueue);

  bool makeRoad (int startRoadY, int startRoadX, int endRoadY, int endRoadX);
};

#endif // SEMESTRAL_WORK_GAME_HPP
