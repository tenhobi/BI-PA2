#ifndef SEMESTRAL_WORK_GAME_HPP
#define SEMESTRAL_WORK_GAME_HPP

#include <string>

#include "Tower.hpp"

#include "Map.hpp"

/**
 * A main class for the tower defense game, which process all initialization, saving, looping etc.
 */
class Game {
public:
  /**
   * A constructor.
   *
   * @param fileName name of a game file
   */
  Game (std::string fileName, bool newGame);

  /**
   * Loads the game from a file.
   *
   * @return success
   */
  bool load ();

  /**
   * Saves the game to a file.
   *
   * @return success
   */
  bool save ();

  /**
   * Process the game.
   */
  void start ();

private:
  /**
   * File name of the input file.
   */
  std::string fileName;

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

  std::vector<Tower> towersInMap;

  /**
   * Loop of the game round.
   */
  void loop ();

  void makeRoad (int startRoadY, int startRoadX, int endRoadY, int endRoadX);
};

#endif // SEMESTRAL_WORK_GAME_HPP
