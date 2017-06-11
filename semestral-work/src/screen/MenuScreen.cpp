#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "../menu/MenuRating.hpp"
#include "../menu/MenuHeading.hpp"
#include "../menu/MenuOption.hpp"
#include "AboutScreen.hpp"
#include "ExitScreen.hpp"
#include "LoadGameScreen.hpp"
#include "NewGameScreen.hpp"
#include "../menu/Menu.hpp"

#include "MenuScreen.hpp"
#include "ErrorScreen.hpp"

// microsecconds
#define DELAY 1000000

int MenuScreen::process () {
  wclear(window);
  wrefresh(window);

  NewGameScreen newGameScreen;
  LoadGameScreen loadGameScreen;
  AboutScreen aboutScreen;
  ExitScreen exitScreen;
  ErrorScreen errorScreen;

  std::vector<MenuOption> menuOptionList = {
     MenuOption(window, "Begin", newGameScreen),
     MenuOption(window, "Load game", loadGameScreen),
     MenuOption(window, "About", aboutScreen),
     MenuOption(window, "Error", errorScreen),
     MenuOption(window, "End", exitScreen)
  };

  MenuHeading heading(window, "Honza Bittner's Tower Defense");
  heading.print((int) menuOptionList.size());

  usleep(DELAY);

  WINDOW* ratingWindow = newwin(1, getmaxx(window), (getmaxy(window) / 2) - (int) (menuOptionList.size() / 2) + 1, 0);
  MenuRating(ratingWindow, "Best console game of the year! ~ gamelife.com").print(0);
  MenuRating(ratingWindow, "Very interesting concept. ~ pcgames.net").print(0);
  MenuRating(ratingWindow, "Kids love it! <3 ~ gamesforkids.eu").print(0);
  wclear(ratingWindow);
  wrefresh(ratingWindow);
  delwin(ratingWindow);

  Menu().process(window, heading, menuOptionList, true);

  return PROCESS_OK;
}
