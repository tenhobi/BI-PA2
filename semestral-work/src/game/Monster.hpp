#ifndef SEMESTRAL_WORK_MONSTER_HPP
#define SEMESTRAL_WORK_MONSTER_HPP

#include <utility>

/**
 * Monster unit of the game.
 */
class Monster {
public:
  /**
   * A constructor.
   *
   * @param health health points
   * @param speed speed
   * @param armor armor points
   */
  Monster (int health, float speed, int armor);

  /**
   * Returns state of monster's health points.
   *
   * @return health amount
   */
  int getHealth ();

  /**
   * Returns state of monster's speed.
   *
   * @return speed coefficient
   */
  float getSpeed ();

  /**
   * Return state of monster's armor.
   *
   * @return armor points
   */
  int getArmor ();

  /**
   * Compares two Monsters by it's properties.
   *
   * @param monster other monster to compare
   *
   * @return boolean which determines the equality.
   */
  bool operator== (const Monster& monster) const;

  /**
   * Coordination of the monster in the gmae map.
   */
  std::pair<int, int> coords;

  /**
   * Position on the road path.
   */
  int pathIndex;

  /**
   * Piece of a step to another map cell.
   */
  float cellPart;

  /**
   * Accepts an attack from sobething.
   *
   * @param power attack power
   */
  void attack (int power);

protected:
  /**
   * Health points.
   */
  int health;

  /**
   * Speed coefficient.
   */
  float speed;

  /**
   * Armor points.
   */
  int armor;
};

#endif // SEMESTRAL_WORK_MONSTER_HPP
