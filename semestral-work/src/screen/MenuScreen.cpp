#include <vector>
#include <unistd.h>
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

// microseconds
#define DELAY 1000000

ScreenState MenuScreen::process () {
  wclear(window);
  wrefresh(window);

  NewGameScreen* newGameScreen = new NewGameScreen;
  LoadGameScreen* loadGameScreen = new LoadGameScreen;
  AboutScreen* aboutScreen = new AboutScreen;
  ExitScreen* exitScreen = new ExitScreen;

  std::vector<MenuOption> menuOptionList = {
     MenuOption(window, "Begin", newGameScreen),
     MenuOption(window, "Load game", loadGameScreen),
     MenuOption(window, "About", aboutScreen),
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

  Menu().process(window, heading, menuOptionList);

  delete newGameScreen;
  delete loadGameScreen;
  delete aboutScreen;
  delete exitScreen;

  return ScreenState::CONTINUE;
}
