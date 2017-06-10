#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "../menu/MenuRating.hpp"
#include "../menu/MenuHeading.hpp"
#include "../menu/MenuOption.hpp"
#include "AboutScreen.hpp"
#include "ExitScreen.hpp"

#include "MenuScreen.hpp"

// microsecconds
#define DELAY 1000000

// For some odd reason the KEY_ENTER is not the enter key. This should be the enter key code.
#define REAL_ENTER_KEY 10

int MenuScreen::process () const {
  MenuHeading heading(window, "Honza Bittner's Tower Defense");
  heading.print();

  usleep(DELAY);

  WINDOW* subtexts = newwin(1, getmaxx(window), (getmaxy(window) / 2) - 3 - 0, 0);
  MenuRating(subtexts, "Best console game of the year! ~ gamelife.com").print();
  MenuRating(subtexts, "Very interesting concept. ~ pcgames.net").print();
  MenuRating(subtexts, "Kids love it! <3 ~ gamesforkids.eu").print();
  wclear(subtexts);
  wrefresh(subtexts);
  delwin(subtexts);

  heading.activate();

  AboutScreen aboutScreen;
  ExitScreen exitScreen;

  std::vector<MenuOption> menuOptionList = {
    MenuOption(window, "Start new game", aboutScreen),
    MenuOption(window, "Load game", aboutScreen),
    MenuOption(window, "About", aboutScreen),
    MenuOption(window, "Exit", exitScreen)
  };

  int pressedKey;
  bool isLooping = true;
  int active = 0;

  keypad(stdscr, TRUE);

  while (isLooping) {
    int offsetCounter = 1;
    int index = 0;

    for (MenuOption& mo: menuOptionList) {
      mo.print(offsetCounter++, index == active);
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
        if (menuOptionList[active].process() == SCREEN_EXIT) {
          isLooping = false;
        }
        break;
      default:
        break;
    }

    wrefresh(window);
  }

  delwin(window);
  return SCREEN_OK;
}
