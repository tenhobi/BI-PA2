#include "AboutScreen.hpp"

int AboutScreen::process () const {
  WINDOW* aboutBoxWindow = newwin(getmaxy(window) / 2, getmaxx(window) / 2,
                                  (getmaxy(window) / 4), (getmaxx(window) / 4));
  WINDOW* aboutWindow = newwin((getmaxy(window) / 2) - 2, (getmaxx(window) / 2) - 2,
                               (getmaxy(window) / 4) + 1, (getmaxx(window) / 4) + 1);

  box(aboutBoxWindow, 0, 0);

  mvwprintw(aboutWindow, 0, 0,
            "This Tower Defense game by Honza Bittner is one of a kind. The game had win multiple awards for the concept, play time, kid friendliness and much more."
              "\n\nPlayer has to protect the kingdom and save us all using towers and awesome upgrade system."
              "\n\nYou will find more info, screenshots, ... on the honzabittner.cz webpage.");

  wrefresh(window);
  wrefresh(aboutBoxWindow);
  wrefresh(aboutWindow);

  getch();

  wclear(window);
  wclear(aboutBoxWindow);
  wclear(aboutWindow);

  wrefresh(window);
  wrefresh(aboutBoxWindow);
  wrefresh(aboutWindow);

  delwin(aboutBoxWindow);
  delwin(aboutWindow);

  return SCREEN_OK;
}
