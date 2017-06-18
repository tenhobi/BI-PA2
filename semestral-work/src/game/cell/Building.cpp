#include "Building.hpp"

bool Building::isEmpty () const {
  return false;
}

Building::Building (Tower* tower) : tower(tower) {}

Tower* Building::getTower () const {
  return tower;
}
