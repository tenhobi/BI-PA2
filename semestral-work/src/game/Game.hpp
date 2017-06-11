#ifndef SEMESTRAL_WORK_GAME_HPP
#define SEMESTRAL_WORK_GAME_HPP

#include "../Processable.hpp"

#include "Map.hpp"

/**
 * A main class for the tower defense game, which process all initialization, saving, looping etc.
 */
class Game : public Processable {
public:
  /**
   * A constructor.
   *
   * @param fileName name of a game file
   */
  Game (std::string fileName);

  void load ();

  void save ();

  int process () override;

private:
  int round;
  int invasionLimit;
  int invasionCount;
  bool saved = false;
  bool finished;
  Map map;
  std::string fileName;

  void loop ();
};

#endif // SEMESTRAL_WORK_GAME_HPP
