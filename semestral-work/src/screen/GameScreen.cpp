#include "../game/Game.hpp"

#include "ErrorScreen.hpp"

#include "GameScreen.hpp"

GameScreen::GameScreen (std::string fileName) : fileName(fileName) {}

int GameScreen::process () {
  Game game(fileName);

  if (!game.load()) {
    ErrorScreen error;
    error.process("Load error from " + fileName + " game file.");
    return SCREEN_CONTINUE;
  }

  game.start();

  return SCREEN_EXIT;
}
