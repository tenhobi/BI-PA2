#include "InfoScreen.hpp"
#include "../ColorPairGenerator.hpp"

#include "ErrorScreen.hpp"

ErrorScreen::ErrorScreen () : InfoScreen() {
  color = ColorPairGenerator::addColor(COLOR_RED, 0);
  activeColor = ColorPairGenerator::addColor(COLOR_RED + SW_COLOR_BRIGHT, 0);
  headingText = "ERROR";
}
