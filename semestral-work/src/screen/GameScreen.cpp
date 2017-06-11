#include "../game/Game.hpp"

#include "ErrorScreen.hpp"

#include "GameScreen.hpp"

GameScreen::GameScreen (std::string fileName) : fileName(fileName) {}

int GameScreen::process () {
//  Game game(fileName);

  ErrorScreen error;
  error.process("Wrong game load file input!");

//  if (game.process() == PROCESS_INPUT_ERROR) {

//    return PROCESS_BACK;
//  }

  return PROCESS_OK;
}
