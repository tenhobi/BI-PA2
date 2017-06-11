#ifndef SEMESTRAL_WORK_GAME_HPP
#define SEMESTRAL_WORK_GAME_HPP

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
  Game (std::string fileName);

  /**
   * Loads the game from a file.
   *
   * @return success
   */
  bool load ();

  /**
   * Saves the game to a file.
   */
  void save ();

  /**
   * Process the game.
   */
  void start ();

private:
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
   * Map data.
   */
  Map map;

  /**
   * File name of the input file.
   */
  std::string fileName;

  /**
   * Loop of the game round.
   */
  void loop ();
};

#endif // SEMESTRAL_WORK_GAME_HPP
