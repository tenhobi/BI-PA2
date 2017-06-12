#ifndef SEMESTRAL_WORK_GAME_HPP
#define SEMESTRAL_WORK_GAME_HPP

#include <string>
#include <queue>
#include <vector>
#include <ncurses.h>

#include "Tower.hpp"
#include "Monster.hpp"
#include "Map.hpp"

/**
 * Determines a state of the game.
 */
enum GameState {
  FINISHED,
  LOST,
  IN_PROGRESS
};

/**
 * A main class for the tower defense game, which process all initialization, saving, looping etc.
 */
class Game {
public:

  /**
   * Returns map height.
   *
   * @return map height
   */
  int getMapHeight ();

  /**
   * Return map width.
   *
   * @return map width
   */
  int getMapWidth ();

  /**
   * Returns number of tower types.
   *
   * @return number of tower type
   */
  int getNumberOfTowerTypes ();

  /**
   * Adds a tower to the game, if it complies all rules.
   *
   * @param type tower type
   * @param y y coordination in the map
   * @param x x coordination in the map
   *
   * @return boolean which detemines the success
   */
  bool addTower (int type, int y, int x);

  /**
   * A constructor.
   */
  Game (bool newGame);

  /**
   * A destructor.
   */
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
  GameState nextRound (WINDOW* gameWindow, WINDOW* statsWindow, WINDOW* towerWindow);

  /**
   * Prints the game windows.
   *
   * @param gameWindow ncurses game window
   * @param statsWindow ncurses statistic window
   * @param towersWindow ncurses towers information window
   *
   * @return game state
   */
  GameState print (WINDOW* gameWindow, WINDOW* statsWindow, WINDOW* towersWindow);

  /**
   * Prints the game windows with or without visible road.
   *
   * @param gameWindow ncurses game window
   * @param statsWindow ncurses statistic window
   * @param towersWindow ncurses towers information window
   * @param showRoad determines if the road cells should be visible
   *
   * @return game state
   */
  GameState print (WINDOW* gameWindow, WINDOW* statsWindow, WINDOW* towersWindow, bool showRoad);

protected:
  /**
   * Determines the type of the game, if it's new or loaded from save.
   */
  bool newGame;

  /**
   * Map data with cells.
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

  /**
   * List with types of towers.
   */
  std::vector<Tower> towerTypeList;

  /**
   * List with towers which are in map.
   */
  std::vector<Tower*> towersInMap;

  /**
   * List with types of monsters.
   */
  std::vector<Monster> monsterTypeList;

  /**
   * List with monsters which are in map.
   */
  std::vector<Monster> monstersInMap;

  /**
   * List of steps of the game road.
   */
  std::vector<std::pair<int, int>> roadList;

  /**
   * Starting coordinations.
   */
  std::pair<int, int> startCoords;

  /**
   * Letter for next tower.
   */
  int towerLetter = 'A';

  /**
   * Road path search function.
   *
   * @param mapCells map of connections between cells.
   * @param mapQueue queue of cells to process
   */
  void bfs (std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>& mapCells,
            std::queue<std::pair<int, int>>& mapQueue);

  /**
   * Makes a road using BFS function.
   *
   * @param startRoadY Y axis of start of road cell
   * @param startRoadX X axis of start of road cell
   * @param endRoadY Y axis of end of road cell
   * @param endRoadX X axis of end of road cell
   *
   * @return boolean which determines if road can me build
   */
  bool makeRoad (int startRoadY, int startRoadX, int endRoadY, int endRoadX);
};

#endif // SEMESTRAL_WORK_GAME_HPP
