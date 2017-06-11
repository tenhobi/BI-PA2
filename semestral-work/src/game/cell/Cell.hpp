#ifndef SEMESTRAL_WORK_CELL_HPP
#define SEMESTRAL_WORK_CELL_HPP

#include <vector>

#include "../Monster.hpp"

/**
 * Cell of the map.
 */
class Cell {
public:
  /**
   * A constructor.
   */
  Cell ();

  /**
   * Virtual destructor.
   */
  virtual ~Cell ();

  /**
   * Adds specific monster to a monster list of this cell.
   *
   * @param monster monster to add to the list of monsters
   */
  virtual void addMonster (Monster monster);

  /**
   * Removes specific monster from the monster list.
   *
   * @param monster monster to remove from the list of monsters
   */
  virtual void removeMonster (Monster monster);

  /**
   * Determines if the cell is empty, e.g. can be build on top of it.
   *
   * @return boolean which determines if can be build on top of this cell
   */
  virtual bool isEmpty () const;

protected:
  /**
   * List of monsters in this cell.
   */
  std::vector<Monster> monsterList;
};

#endif // SEMESTRAL_WORK_CELL_HPP
