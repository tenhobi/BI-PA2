#ifndef SEMESTRAL_WORK_BUILDING_HPP
#define SEMESTRAL_WORK_BUILDING_HPP

#include "../Tower.hpp"

#include "Cell.hpp"

/**
 * Building in the map.
 */
class Building : public Cell {
public:
  Building (Tower* tower);

  /**
   * The building can not be build on top of another building, so this is not an empty cell.
   *
   * @return always false
   */
  bool isEmpty () const override;

  Tower* getTower ();

protected:
  /**
   * Tower which is on top of this building cell.
   */
  Tower* tower;
};

#endif // SEMESTRAL_WORK_BUILDING_HPP
