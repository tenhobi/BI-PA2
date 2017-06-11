#include <ncurses.h>

#include "../game/Game.hpp"
#include "ErrorScreen.hpp"

#include "GameScreen.hpp"
#include "../ColorPairGenerator.hpp"

#define MARGIN 1
#define INPUT_SIZE (10 + 1)

GameScreen::GameScreen (std::string fileName, bool newGame) : fileName(fileName), newGame(newGame) {}

ScreenState GameScreen::process () {
  ErrorScreen errorScreen;
  InfoScreen infoScreen;

  Game game(newGame);

  if (!game.load(fileName)) {
    errorScreen.process("Load of the game from file " + fileName + " was terminated.");
    return ScreenState::CONTINUE;
  }

  wclear(window);
  wrefresh(window);

  mvwprintw(window, 0, 0, std::to_string(game.getMapWidth()).c_str());
  mvwprintw(window, 1, 0, std::to_string(game.getMapHeight()).c_str());

  WINDOW* gameWindow = newwin(game.getMapHeight(),
                              game.getMapWidth(),
                              MARGIN,
                              (getmaxx(window) / 2) - (game.getMapWidth() / 2));

  WINDOW* commandWindow = newwin(1,
                                 INPUT_SIZE,
                                 MARGIN + game.getMapHeight() + MARGIN,
                                 (getmaxx(window) / 2) - (INPUT_SIZE / 2));

  WINDOW* statsWindow = newwin(3,
                               getmaxx(window),
                               MARGIN + game.getMapHeight() + 3 * MARGIN,
                               (getmaxx(window) / 2) - (INPUT_SIZE / 2));

  wbkgd(gameWindow, COLOR_PAIR(ColorPairGenerator::addColor(0, COLOR_BLUE)));
  wrefresh(gameWindow);

  wbkgd(commandWindow, COLOR_PAIR(ColorPairGenerator::addColor(0, COLOR_GREEN)));
  wrefresh(commandWindow);

  char input[INPUT_SIZE + 5];
  std::string inputCommand;

  if (game.print(gameWindow, statsWindow) == GameState::FINISHED) {
    infoScreen.process("The game has been already finished.");
    return ScreenState::CONTINUE;
  }

  while (true) {
    wbkgd(gameWindow, COLOR_PAIR(ColorPairGenerator::addColor(0, COLOR_BLUE)));
    wclear(gameWindow);
    wrefresh(gameWindow);

    wbkgd(commandWindow, COLOR_PAIR(ColorPairGenerator::addColor(0, COLOR_GREEN)));
    wclear(commandWindow);
    wrefresh(commandWindow);

    wclear(statsWindow);
    wrefresh(statsWindow);

    game.print(gameWindow, statsWindow);

    // print map
    // print towers
    // print money, round, invasion

    // turn on cursor
    echo();
    curs_set(TRUE);

    // wait for input
    mvwgetnstr(commandWindow, 0, 0, input, INPUT_SIZE);

    // turn off cursor
    noecho();
    curs_set(FALSE);

    // clear command
    wclear(commandWindow);
    wrefresh(commandWindow);

    // TODO
    mvwprintw(window, 3, 0, input);
    wrefresh(window);

    inputCommand = std::string(input);

    if (inputCommand == "exit") {
      return ScreenState::EXIT;
    } else if (inputCommand == "save") {
      infoScreen.process("Write the name of the file into the command window.");
      wclear(gameWindow);
      wbkgd(gameWindow, COLOR_PAIR(ColorPairGenerator::addColor(0, COLOR_BLUE)));
      wrefresh(gameWindow);

      wclear(commandWindow);
      wbkgd(commandWindow, COLOR_PAIR(ColorPairGenerator::addColor(0, COLOR_GREEN)));
      wrefresh(commandWindow);

      wclear(statsWindow);
      wrefresh(statsWindow);

      // turn on cursor
      echo();
      curs_set(TRUE);

      // wait for input
      mvwgetnstr(commandWindow, 0, 0, input, INPUT_SIZE);

      // turn off cursor
      noecho();
      curs_set(FALSE);

      // clear command
      wclear(commandWindow);
      wrefresh(commandWindow);

      inputCommand = std::string(input);

      game.save(inputCommand);
    } else if (inputCommand == "tower") {
      infoScreen.process("Write the type of the tower and it's Y and X of the left top corner. Like '1 23 12'");

      // turn on cursor
      echo();
      curs_set(TRUE);

      // wait for input
      mvwgetnstr(commandWindow, 0, 0, input, INPUT_SIZE);

      // turn off cursor
      noecho();
      curs_set(FALSE);

      // clear command
      wclear(commandWindow);
      wrefresh(commandWindow);

      inputCommand = std::string(input);

      // TODO: get the input to the stream and read
//      std::stringstream inputCommandStream;
//
//      int type, y, x;
//
//      inputCommandStream >> type >> y >> x;
    } else {
      game.nextRound(gameWindow, statsWindow);
    }
  }
}
