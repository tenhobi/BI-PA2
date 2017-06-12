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

  /**
   * Height of the map.
   */
  int height;

  /**
   * Width of the map.
   */
  int width;

  /**
   * A constructor.
   *
   * @param height height of the map
   * @param width width of the map
   */
  Map (int height, int width);

  /**
   * Destructor.
   */
  ~Map ();

  /**
   * Resizes the map's data by it's height and width.
   */
  void resize ();
};

#endif // SEMESTRAL_WORK_MAP_HPP
