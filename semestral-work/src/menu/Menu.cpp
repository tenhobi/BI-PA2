#include <ncurses.h>

#include "../Config.hpp"
#include "MenuHeading.hpp"
#include "MenuOption.hpp"

#include "Menu.hpp"

void Menu::process (WINDOW* window, MenuHeading heading, std::vector<MenuOption>& items) {
  int pressedKey;
  bool isLooping = true;
  int active = 0;

  // Disable cursor.
  noecho();
  curs_set(FALSE);

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
      case SW_KEY_ENTER:
      case KEY_RIGHT:
//        puts("\a");

        switch (items[active].process()) {
          case ScreenState::EXIT:
            isLooping = false;
            break;
          default:
            break;
        }

        wclear(window);
        wrefresh(window);

        break;
      default:
        break;
    }

    wrefresh(window);
  }
}
