#ifndef SEMESTRAL_WORK_TOWER_HPP
#define SEMESTRAL_WORK_TOWER_HPP

#include <vector>

#include "cell/Cell.hpp"

/**
 * Tower component which has the purpose of destroying invading monsters.
 */
class Tower {
public:

  /**
   * Y position in game map.
   */
  int y;

  /**
   * X position in game map.
   */
  int x;

  /**
   * Letter of the tower in the map.
   */
  int letter;

  /**
   * In-time amount of ammo of this tower.
   */
  int currentAmmo;

  /**
   * A full-fledged constructor.
   *
   * @param cost
   * @param height
   * @param width
   * @param attackPower
   * @param range
   * @param ammoPerRound
   */
  Tower (int cost, int height, int width, int attackPower, int range, int ammoPerRound);

  /**
   * A copy constructor from another tower.
   *
   * @param tower
   */
  Tower (const Tower& tower);

  /**
   * Return the cost of the tower.
   *
   * @return cost amount
   */
  int getCost ();

  /**
   * Return the height of the tower.
   *
   * @return height
   */
  int getHeight ();

  /**
   * Returns the width of the tower.
   *
   * @return width
   */
  int getWidth ();

  /**
   * Returns the attack power of the tower.
   *
   * @return attack power
   */
  int getAttackPower ();

  /**
   * Return the range of the tower.
   *
   * @return tower range
   */
  int getRange ();

  /**
   * Return the default ammo per round.
   *
   * @return ammo per round
   */
  int getAmmoPerRound ();


  /**
   * Initialize all round-dependent properties.
   */
  void initRound ();

  /**
   * Determines if the tower is equal to another by it's properties.
   *
   * @param tower tower to compare
   *
   * @return boolean which determines the equality
   */
  bool operator== (const Tower tower) const;

protected:
  /**
   * Tower cost amount.
   */
  int cost;

  /**
   * Cell's height.
   */
  int height;

  /**
   * Cell's width.
   */
  int width;

  /**
   * Attack power of the tower.
   */
  int attackPower;

  /**
   * Tower's range.
   */
  int range;

  /**
   * Default per-round ammo amount;
   */
  int ammoPerRound;
};

#endif // SEMESTRAL_WORK_TOWER_HPP
