#ifndef SEMESTRAL_WORK_MONSTER_HPP
#define SEMESTRAL_WORK_MONSTER_HPP

#include <utility>

class Monster {
public:
  Monster (int health, float speed, int armor);

  int getHealth ();

  float getSpeed ();

  int getArmor ();

  bool operator== (const Monster& monster) const;

  std::pair<int, int> coords;

  int pathIndex;

  float cellPart;

protected:
  int health;
  float speed;
  int armor;
};

#endif // SEMESTRAL_WORK_MONSTER_HPP
