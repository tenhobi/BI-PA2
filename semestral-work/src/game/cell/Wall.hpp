#ifndef SEMESTRAL_WORK_WALL_HPP
#define SEMESTRAL_WORK_WALL_HPP

#include "Cell.hpp"

/**
 * Wall cell in the map.
 */
class Wall : public Cell {
  /**
   * Wall is not where you can build.
   *
   * @return always false.
   */
  bool isEmpty () const override;
};

#endif // SEMESTRAL_WORK_WALL_HPP
