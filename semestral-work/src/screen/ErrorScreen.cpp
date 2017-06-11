#include "ErrorScreen.hpp"

int ErrorScreen::process () {
  return process("Error occurred.");
}

int ErrorScreen::process (std::string text) {
  wclear(window);
  wrefresh(window);

  wattron(window, COLOR_PAIR(color));
  mvwprintw(window, (getmaxy(window)) / 2, (getmaxx(window)) / 2 - (int) (text.size() / 2), text.c_str());
  wattroff(window, COLOR_PAIR(color));

  wrefresh(window);

  // Use blocking read.
  timeout(-1);
  getch();

  wclear(window);
  wrefresh(window);

  return PROCESS_OK;
}
