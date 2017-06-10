#ifndef SEMESTRAL_WORK_GAME_HPP
#define SEMESTRAL_WORK_GAME_HPP

#include "../Processable.hpp"

#include "Map.hpp"

/**
 * A main class for the tower defense game, which process all initialization, saving, looping etc.
 */
class Game: public Processable {
public:
  /**
   * A constructor.
   */
  Game ();

  /**
   * A constructor with defined invasion limit and map.
   * @param invasionLimit
   * @param map
   */
  Game (int invasionLimit, Map map);

  void load ();

  void save () const;

  void start ();

  int process() override;

private:
  int round;
  int invasionLimit;
  int invasionCount;
  bool finished;
  Map map;

  void loop ();

  void close ();
};

#endif // SEMESTRAL_WORK_GAME_HPP
