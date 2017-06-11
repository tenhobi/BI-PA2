#ifndef SEMESTRAL_WORK_MONSTER_HPP
#define SEMESTRAL_WORK_MONSTER_HPP

class Monster {
public:
  Monster (int health, float speed, int armor);

  int getHealth ();

  float getSpeed ();

  int getArmor ();

private:
  int health;
  float speed;
  int armor;
};

#endif // SEMESTRAL_WORK_MONSTER_HPP
