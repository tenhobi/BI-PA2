#include <ncurses.h>

#include "ColorPairGenerator.hpp"

short ColorPairGenerator::addColor (short text, short background) {
  init_pair(counter, text, background);
  return counter++;
}

ColorPairGenerator::ColorPairGenerator () {}

short ColorPairGenerator::counter = 1;
