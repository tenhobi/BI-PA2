#include "ErrorScreen.hpp"

int ErrorScreen::process () {
  return process("Error occurred.");
}

int ErrorScreen::process (std::string text) {
  wclear(window);
  wrefresh(window);

  std::string headingText = "ERROR";

  wattron(window, COLOR_PAIR(color));
  mvwprintw(window, ((getmaxy(window)) / 2) - 1, (getmaxx(window)) / 2 - (int) (headingText.size() / 2), headingText.c_str());
  wattroff(window, COLOR_PAIR(color));

  wattron(window, COLOR_PAIR(activeColor));
  mvwprintw(window, ((getmaxy(window)) / 2) + 1, (getmaxx(window)) / 2 - (int) (text.size() / 2), text.c_str());
  wattroff(window, COLOR_PAIR(activeColor));

  wrefresh(window);

  // Use blocking read.
  timeout(-1);
  getch();

  wclear(window);
  wrefresh(window);

  return SCREEN_OK;
}
