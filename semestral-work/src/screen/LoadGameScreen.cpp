#include <dirent.h>
#include <iostream>
#include <regex>
#include <unistd.h>

#include "../menu/MenuOption.hpp"
#include "../game/Game.hpp"
#include "../menu/MenuHeading.hpp"
#include "BackScreen.hpp"

#include "LoadGameScreen.hpp"

int LoadGameScreen::process () {
  wclear(window);
  wrefresh(window);

  DIR* mapDir;
  struct dirent* file;

  mapDir = opendir("./data/map");

  int counter = 0;

  if (mapDir != NULL) {
    while ((file = readdir(mapDir))) {
      if (std::regex_match(file->d_name, std::regex("(.+)(\\.map)"))) {
        mvwprintw(window, counter++, 0, file->d_name);
      }
    }
  }

  wrefresh(window);

  Game game;
  BackScreen back;

  std::vector<MenuOption> menuOptionList = {
    MenuOption(window, "one", game),
    MenuOption(window, "two", game),
    MenuOption(window, "three", game),
    MenuOption(window, "back to main menu", back)
  };

  MenuHeading heading(window, "Load game");
  heading.print((int) menuOptionList.size());

  usleep(SCREEN_DELAY);

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
        isLooping = false;

        wclear(window);
        wrefresh(window);

        if (menuOptionList[active].process() == PROCESS_BACK) {
          //
        }
        break;
      default:
        break;
    }

    wrefresh(window);
  }

  return PROCESS_OK;
}
