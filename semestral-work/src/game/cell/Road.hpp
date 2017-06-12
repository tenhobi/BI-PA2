#ifndef SEMESTRAL_WORK_ROAD_HPP
#define SEMESTRAL_WORK_ROAD_HPP

#include "../Monster.hpp"

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
   * Adds specific monster to a monster list of this cell.
   *
   * @param monster monster to add to the list of monsters
   */
  void addMonster (Monster monster);

  /**
   * Removes specific monster from the monster list.
   *
   * @param monster monster to remove from the list of monsters
   */
  void removeMonster (Monster monster);

  /**
   * Road is always not empty.
   *
   * @return always false
   */
  bool isEmpty () const override;

  RoadState getState ();

  std::pair<int, int> next;

  /**
   * List of monsters in this cell.
   */
  std::vector<Monster> monsterList;

protected:
  /**
   * State of the road cell.
   */
  RoadState state;
};

#endif // SEMESTRAL_WORK_ROAD_HPP
