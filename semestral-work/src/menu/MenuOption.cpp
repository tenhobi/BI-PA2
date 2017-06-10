#include <unistd.h>

#include "MenuOption.hpp"

// microseconds
#define DELAY 0

MenuOption::MenuOption (WINDOW* window, const std::string text, Screen& screen) : MenuItem(window, text),
                                                                                  screen(screen) {}

void MenuOption::print (int offset, bool active) const {
  if (active) {
    wattron(window, COLOR_PAIR(colorActive));
    mvwprintw(window, ((getmaxy(window)) / 2) - 3 + offset, (getmaxx(window) - (int) text.size()) / 2, ctext);
    wattroff(window, COLOR_PAIR(colorActive));
  } else {
    wattron(window, COLOR_PAIR(color));
    mvwprintw(window, ((getmaxy(window)) / 2) - 3 + offset, (getmaxx(window) - (int) text.size()) / 2, ctext);
    wattroff(window, COLOR_PAIR(color));
  }

  wrefresh(window);
  usleep(DELAY);
}

void MenuOption::print () const {
  print(0, false);
}

int MenuOption::process () const {
  return screen.process();
}
