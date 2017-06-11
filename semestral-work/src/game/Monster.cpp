#include "Monster.hpp"

Monster::Monster (int health, float speed, int armor) : health(health), speed(speed), armor(armor) {}

int Monster::getHealth () {
  return health;
}

float Monster::getSpeed () {
  return speed;
}

int Monster::getArmor () {
  return armor;
}
