#include <ncurses.h>
#include <string>

#include "InfoScreen.hpp"

int InfoScreen::process () {
  return process("Unspecified info.", -1);
}

int InfoScreen::process (std::string text) {
  return process(text, -1);
}

int InfoScreen::process (std::string text, int time) {
  wclear(window);
  wrefresh(window);

  std::string headingText = "INFO";

  wattron(window, COLOR_PAIR(color));
  mvwprintw(window, ((getmaxy(window)) / 2) - 1, (getmaxx(window)) / 2 - (int) (headingText.size() / 2), headingText.c_str());
  wattroff(window, COLOR_PAIR(color));

  wattron(window, COLOR_PAIR(activeColor));
  mvwprintw(window, ((getmaxy(window)) / 2) + 1, (getmaxx(window)) / 2 - (int) (text.size() / 2), text.c_str());
  wattroff(window, COLOR_PAIR(activeColor));

  wrefresh(window);

  // Use blocking read.
  timeout(time);
  getch();

  wclear(window);
  wrefresh(window);

  return SCREEN_CONTINUE;
}
