#ifndef SEMESTRAL_WORK_ROAD_HPP
#define SEMESTRAL_WORK_ROAD_HPP

#include "Cell.hpp"

enum RoadState {
  NORMAL,
  START,
  END
};

/**
 * Road cell of the map.
 */
class Road : public Cell {
public:
  /**
   * A constructor to the road cell.
   *
   * @param state determines the state of the road
   */
  Road (RoadState state);

  /**
   * Road is always not empty.
   *
   * @return always false
   */
  bool isEmpty () const override;

  RoadState getState ();

protected:
  /**
   * State of the road cell.
   */
  RoadState state;
};

#endif // SEMESTRAL_WORK_ROAD_HPP
