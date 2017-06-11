#include "../game/Game.hpp"
#include "ErrorScreen.hpp"

#include "GameScreen.hpp"

GameScreen::GameScreen (std::string fileName, bool newGame) : fileName(fileName), newGame(newGame) {}

int GameScreen::process () {
  Game game(fileName, newGame);

  if (!game.load()) {
    ErrorScreen errorScreen;
    errorScreen.process("Load of the game from file " + fileName + " was terminated.");
    return SCREEN_CONTINUE;
  }

  game.save();

  game.start();

  return SCREEN_EXIT;
}
