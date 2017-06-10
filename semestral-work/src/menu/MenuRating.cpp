#include <unistd.h>
#include <string>

#include "MenuRating.hpp"

// milliseconds
#define DELAY 2500

MenuRating::MenuRating (WINDOW* window, const std::string text) : MenuItem(window, text) {}

void MenuRating::print () const {
  wclear(window);

  mvwprintw(window, 0, (getmaxx(window) - (int) text.size()) / 2, ctext);

  wrefresh(window);

  timeout(DELAY);
  getch();
}

