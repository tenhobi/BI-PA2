#include "../Monster.hpp"

#include "Road.hpp"

Road::Road (RoadState state) : state(state) {}

bool Road::isEmpty () const {
  return false;
}

RoadState Road::getState () const {
  return state;
}
