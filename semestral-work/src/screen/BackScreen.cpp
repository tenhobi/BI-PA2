#include "BackScreen.hpp"

int BackScreen::process () {
  wclear(window);
  wrefresh(window);

  getch();

  wclear(window);
  wrefresh(window);

  return PROCESS_BACK;
}
