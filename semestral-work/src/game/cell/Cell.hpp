#ifndef SEMESTRAL_WORK_CELL_HPP
#define SEMESTRAL_WORK_CELL_HPP

#include <vector>

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
   * Determines if the cell is empty, e.g. can be build on top of it.
   *
   * @return boolean which determines if can be build on top of this cell
   */
  virtual bool isEmpty () const;

protected:

};

#endif // SEMESTRAL_WORK_CELL_HPP
