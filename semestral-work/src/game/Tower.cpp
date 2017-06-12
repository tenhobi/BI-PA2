#include "Tower.hpp"

Tower::Tower (int cost, int height, int width, int attackPower, int range, int ammoPerRound) : cost(cost),
                                                                                               height(height),
                                                                                               width(width),
                                                                                               attackPower(attackPower),
                                                                                               range(range),
                                                                                               ammoPerRound(
                                                                                                 ammoPerRound) {}

Tower::Tower (const Tower& tower) : cost(tower.cost),
                                    height(tower.height),
                                    width(tower.width),
                                    attackPower(tower.attackPower),
                                    range(tower.range),
                                    ammoPerRound(tower.ammoPerRound) {}

int Tower::getCost () {
  return cost;
}

int Tower::getHeight () {
  return height;
}

int Tower::getWidth () {
  return width;
}

int Tower::getAttackPower () {
  return attackPower;
}

int Tower::getRange () {
  return range;
}

int Tower::getAmmoPerRound () {
  return ammoPerRound;
}

bool Tower::operator== (const Tower b) const {
  return
    cost == b.cost &&
    height == b.height &&
    width == b.width &&
    attackPower == b.attackPower &&
    range == b.range &&
    ammoPerRound == b.ammoPerRound;
}

void Tower::initRound () {
  currentAmmo = ammoPerRound;
}

