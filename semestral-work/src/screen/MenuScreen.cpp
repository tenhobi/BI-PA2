#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "../menu/MenuRating.hpp"
#include "../menu/MenuHeading.hpp"
#include "../menu/MenuOption.hpp"
#include "AboutScreen.hpp"
#include "ExitScreen.hpp"
#include "LoadGameScreen.hpp"
#include "NewGameScreen.hpp"

#include "MenuScreen.hpp"

// microsecconds
#define DELAY 1000000

int MenuScreen::process () {
  wclear(window);
  wrefresh(window);

  NewGameScreen newGameScreen;
  LoadGameScreen loadGameScreen;
  AboutScreen aboutScreen;
  ExitScreen exitScreen;

  std::vector<MenuOption> menuOptionList = {
    MenuOption(window, "Begin", newGameScreen),
    MenuOption(window, "Load game", loadGameScreen),
    MenuOption(window, "About", aboutScreen),
    MenuOption(window, "End", exitScreen)
  };

  MenuHeading heading(window, "Honza Bittner's Tower Defense");
  heading.print((int) menuOptionList.size());

  usleep(DELAY);

  WINDOW* ratingWindow = newwin(1, getmaxx(window), (getmaxy(window) / 2) - (int) (menuOptionList.size() / 2) + 1, 0);
  MenuRating(ratingWindow, "Best console game of the year! ~ gamelife.com").print(0);
  MenuRating(ratingWindow, "Very interesting concept. ~ pcgames.net").print(0);
  MenuRating(ratingWindow, "Kids love it! <3 ~ gamesforkids.eu").print(0);
  wclear(ratingWindow);
  wrefresh(ratingWindow);
  delwin(ratingWindow);

  int pressedKey;
  bool isLooping = true;
  int active = 0;

  keypad(stdscr, TRUE);

  while (isLooping) {
    int offsetCounter = 1;
    int index = 0;

    heading.activePrint((int) menuOptionList.size());

    for (MenuOption& mo: menuOptionList) {
      mo.print((int) menuOptionList.size(), offsetCounter++, index == active);
      index++;
    }

    // Use blocking read.
    timeout(-1);
    pressedKey = getch();

    switch (pressedKey) {
      case KEY_UP:
        active--;
        if (active < 0) {
          active = (int) menuOptionList.size() - 1;
        }
        break;
      case KEY_DOWN:
        active++;
        if (active >= (int) menuOptionList.size()) {
          active = 0;
        }
        break;
      case REAL_ENTER_KEY:
      case KEY_RIGHT:
        puts("\a");
        if (menuOptionList[active].process() == PROCESS_EXIT) {
          isLooping = false;
        }
        break;
      default:
        break;
    }

    wrefresh(window);
  }

  return PROCESS_OK;
}
