#include "BackScreen.hpp"

int BackScreen::process () {
  if (exit) {
    return SCREEN_EXIT;
  }

  return SCREEN_CONTINUE;
}

BackScreen::BackScreen (bool exit) : exit(exit) {}
