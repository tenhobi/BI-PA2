#include <ncurses.h>

#include "MenuHeading.hpp"

#include "Menu.hpp"

void Menu::process (WINDOW* window, MenuHeading heading, std::vector<MenuOption> items, bool exit) {
  int pressedKey;
  bool isLooping = true;
  int active = 0;

  keypad(stdscr, TRUE);

  while (isLooping) {
    int offsetCounter = 1;
    int index = 0;

    heading.activePrint((int) items.size());

    for (MenuOption& mo: items) {
      mo.print((int) items.size(), offsetCounter++, index == active);
      index++;
    }

    // Use blocking read.
    timeout(-1);
    pressedKey = getch();

    switch (pressedKey) {
      case KEY_UP:
        active--;
        if (active < 0) {
          active = (int) items.size() - 1;
        }
        break;
      case KEY_DOWN:
        active++;
        if (active >= (int) items.size()) {
          active = 0;
        }
        break;
      case REAL_ENTER_KEY:
      case KEY_RIGHT:
        puts("\a");

        if (exit) {
          if (items[active].process() == PROCESS_EXIT) {
            isLooping = false;
          }
        } else {
          isLooping = false;
          wclear(window);
          wrefresh(window);
        }

        break;
      default:
        break;
    }

    wrefresh(window);
  }
}
