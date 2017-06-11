#include "Cell.hpp"

Cell::Cell () {}

Cell::~Cell () {}

void Cell::addMonster (Monster monster) {
  monsterList.push_back(monster);
}

void Cell::removeMonster (Monster monster) {
  // todo: remove monster
}

bool Cell::isEmpty () const {
  return monsterList.empty();
}
