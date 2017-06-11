#include <string>
#include <unistd.h>

#include "ExitScreen.hpp"

int ExitScreen::process () {
  std::string heading = "Thank you for playing this game.";
  std::string note = "This game was developed by Honza Bittner in 2017.";
  std::string link = "Visit honzabittner.cz for more awesomeness!";

  mvwprintw(window, ((getmaxy(window)) / 2) - 2, (getmaxx(window) - (int) heading.size()) / 2, heading.c_str());
  mvwprintw(window, ((getmaxy(window)) / 2) + 0, (getmaxx(window) - (int) note.size()) / 2, note.c_str());
  mvwprintw(window, ((getmaxy(window)) / 2) + 2, (getmaxx(window) - (int) link.size()) / 2, link.c_str());

  wrefresh(window);

  // Use non blocking read.
  timeout(5000);
  getch();

  wclear(window);

  return SCREEN_EXIT;
}
