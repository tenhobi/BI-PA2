#include "BackScreen.hpp"

int BackScreen::process () {
  if (exit) {
    return SCREEN_EXIT;
  }

  return SCREEN_BACK;
}

BackScreen::BackScreen (bool exit): exit(exit) {}
