#include "BackScreen.hpp"

ScreenState BackScreen::process () {
  if (exit) {
    return ScreenState::EXIT;
  }

  return ScreenState::CONTINUE;
}

BackScreen::BackScreen (bool exit) : exit(exit) {}
