#include <ncurses.h>
#include <unistd.h>

#include "MenuHeading.hpp"

// microseconds
#define DELAY 0

MenuHeading::MenuHeading (WINDOW* window, const std::string text) : MenuItem(window, text) {}

void MenuHeading::print (int numberOfItems) const {
  if (active) {
    wattron(window, COLOR_PAIR(activeColor));
    wattron(window, A_UNDERLINE);
    mvwprintw(window, ((getmaxy(window)) / 2) - (int) (numberOfItems / 2) - 1, (getmaxx(window) - (int) text.size()) / 2, ctext);
    wattroff(window, A_UNDERLINE);
  } else {
    wattron(window, COLOR_PAIR(color));
    mvwprintw(window, ((getmaxy(window)) / 2) - (int) (numberOfItems / 2) - 1, (getmaxx(window) - (int) text.size()) / 2, ctext);
  }

  wrefresh(window);
  usleep(DELAY);
}

void MenuHeading::activePrint (int numberOfItems) {
  active = true;
  print(numberOfItems);
}
