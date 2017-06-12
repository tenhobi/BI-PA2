#include "../Monster.hpp"

#include "Road.hpp"

Road::Road (RoadState state) : state(state) {}

void Road::addMonster (Monster monster) {
  monsterList.push_back(monster);
}

void Road::removeMonster (Monster monster) {
  // todo: remove monster
}

bool Road::isEmpty () const {
  return false;
}

RoadState Road::getState () {
  return state;
}
