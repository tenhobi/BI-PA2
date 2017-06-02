#include "Map.hpp"

bool Map::save () const {
  return false;
}

bool Map::load () {
  return false;
}

bool Map::init () {
  return false;
}

int Map::getWidth () const {
  return this->width;
}

int Map::getHeight () const {
  return this->height;
}

Map::operator bool () const {
  return height && width;
}
