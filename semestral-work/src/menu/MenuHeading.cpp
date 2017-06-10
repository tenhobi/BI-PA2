#include <ncurses.h>
#include <unistd.h>

#include "MenuHeading.hpp"

// microseconds
#define DELAY 0

MenuHeading::MenuHeading (WINDOW* window, const std::string text) : MenuItem(window, text) {}

void MenuHeading::print () const {
  if (active) {
    wattron(window, COLOR_PAIR(colorActive));
    wattron(window, A_UNDERLINE);
    mvwprintw(window, ((getmaxy(window)) / 2) - 3 - 2, (getmaxx(window) - (int) text.size()) / 2, ctext);
    wattroff(window, A_UNDERLINE);
  } else {
    wattron(window, COLOR_PAIR(color));
    mvwprintw(window, ((getmaxy(window)) / 2) - 3 - 2, (getmaxx(window) - (int) text.size()) / 2, ctext);
  }

  wrefresh(window);
  usleep(DELAY);
}

void MenuHeading::activate () {
  active = true;
  print();
}
