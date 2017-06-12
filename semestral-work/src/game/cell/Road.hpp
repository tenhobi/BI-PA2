#ifndef SEMESTRAL_WORK_ROAD_HPP
#define SEMESTRAL_WORK_ROAD_HPP

#include "Cell.hpp"

/**
 * State enum for road cell object which determines it's state.
 */
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

  /**
   * Getter of the state.
   *
   * @return state of road
   */
  RoadState getState () const;

  /**
   * Next road cell to the end.
   */
  std::pair<int, int> next;

protected:
  /**
   * State of the road cell.
   */
  RoadState state;
};

#endif // SEMESTRAL_WORK_ROAD_HPP
