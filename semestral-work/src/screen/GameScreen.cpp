#include <ncurses.h>
#include <sstream>

#include "../game/Game.hpp"
#include "ErrorScreen.hpp"
#include "../ColorPairGenerator.hpp"

#include "GameScreen.hpp"

#define MARGIN 1
#define INPUT_SIZE (10 + 1)
#define STATS_HEIGHT 4

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

  WINDOW* statsWindow = newwin(STATS_HEIGHT,
                               getmaxx(window),
                               MARGIN + game.getMapHeight() + 3 * MARGIN,
                               (getmaxx(window) / 2) - (getmaxx(window) / 4));

  WINDOW* towerWindow = newwin(game.getNumberOfTowerTypes() + 1,
                               getmaxx(window) / 2,
                               MARGIN + game.getMapHeight() + 4 * MARGIN + STATS_HEIGHT,
                               (getmaxx(window) / 2) - (getmaxx(window) / 4));

  wbkgd(gameWindow, COLOR_PAIR(ColorPairGenerator::addColor(COLOR_BLACK, COLOR_WHITE)));
  wrefresh(gameWindow);

  wbkgd(commandWindow, COLOR_PAIR(ColorPairGenerator::addColor(COLOR_RED, COLOR_WHITE)));
  wrefresh(commandWindow);

  wrefresh(statsWindow);

  wrefresh(towerWindow);

  // input of command

  char input[INPUT_SIZE + 5];
  std::string inputCommand;

  if (game.print(gameWindow, statsWindow, towerWindow, true) == GameState::FINISHED) {
    infoScreen.process("The game has been already finished.");
    return ScreenState::CONTINUE;
  }

  // loop

  while (true) {
    wclear(gameWindow);
    wclear(commandWindow);
    wclear(statsWindow);
    wclear(towerWindow);

    game.print(gameWindow, statsWindow, towerWindow, true);

    wrefresh(gameWindow);
    wrefresh(commandWindow);
    wrefresh(statsWindow);
    wrefresh(towerWindow);

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

    mvwprintw(window, 3, 0, input);
    wrefresh(window);

    inputCommand = std::string(input);

    // trim input command

    while (!inputCommand.empty() && std::isspace(*inputCommand.begin())) {
      inputCommand.erase(inputCommand.begin());
    }

    while (!inputCommand.empty() && std::isspace(*inputCommand.rbegin())) {
      inputCommand.erase(inputCommand.length() - 1);
    }

    // commands

    if (inputCommand == "exit") {
      wclear(gameWindow);
      wrefresh(gameWindow);

      wclear(commandWindow);
      wrefresh(commandWindow);

      wclear(statsWindow);
      wrefresh(statsWindow);

      wclear(towerWindow);
      wrefresh(towerWindow);

      return ScreenState::EXIT;
    } else if (inputCommand == "save") {
      infoScreen.process("Write the name of the file into the command window.");

      wclear(gameWindow);
      wclear(commandWindow);
      wclear(statsWindow);
      wclear(towerWindow);

      game.print(gameWindow, statsWindow, towerWindow, true);

      wrefresh(gameWindow);
      wrefresh(commandWindow);
      wrefresh(statsWindow);
      wrefresh(towerWindow);

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

      wclear(gameWindow);
      wclear(commandWindow);
      wclear(statsWindow);
      wclear(towerWindow);

      game.print(gameWindow, statsWindow, towerWindow, true);

      wrefresh(gameWindow);
      wrefresh(commandWindow);
      wrefresh(statsWindow);
      wrefresh(towerWindow);

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

      // trim input

      while (!inputCommand.empty() && std::isspace(*inputCommand.begin())) {
        inputCommand.erase(inputCommand.begin());
      }

      while (!inputCommand.empty() && std::isspace(*inputCommand.rbegin())) {
        inputCommand.erase(inputCommand.length() - 1);
      }

      std::stringstream inputCommandStream;
      inputCommandStream.str(inputCommand);

      int type, y, x;

      inputCommandStream >> type >> y >> x;

      if (!game.addTower(type, y, x)) {
        errorScreen.process("Cannot place tower to this place.");
      }
    } else if (inputCommand == "") {
      switch (game.nextRound(gameWindow, statsWindow, towerWindow)) {
        case GameState::IN_PROGRESS:
          break;
        case GameState::FINISHED:
          return ScreenState::EXIT;
        case GameState::LOST:
          game.save("lost-game-results");
          return ScreenState::EXIT;
      }

      game.print(gameWindow, statsWindow, towerWindow, true);

      wrefresh(gameWindow);
      wrefresh(commandWindow);
      wrefresh(statsWindow);
      wrefresh(towerWindow);
    } else {
      errorScreen.process("Wrong command.");
    }
  }
}
