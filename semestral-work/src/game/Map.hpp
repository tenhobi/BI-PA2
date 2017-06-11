#ifndef SEMESTRAL_WORK_MAP_HPP
#define SEMESTRAL_WORK_MAP_HPP

#include <vector>

#include "cell/Cell.hpp"

/**
 * Map data holder of a game.
 */
class Map {
public:
  /**
  * Map data, contains cells.
  */
  std::vector<std::vector<Cell*>> data;

  int height;
  int width;

  Map (int height, int width);

  ~Map ();

  void resize ();
};

#endif // SEMESTRAL_WORK_MAP_HPP
