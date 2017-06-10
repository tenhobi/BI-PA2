#include <dirent.h>
#include <iostream>
#include <regex>
#include <unistd.h>

#include "../menu/MenuOption.hpp"
#include "../game/Game.hpp"
#include "../menu/MenuHeading.hpp"
#include "BackScreen.hpp"
#include "../menu/Menu.hpp"

#include "LoadGameScreen.hpp"

int LoadGameScreen::process () {
  wclear(window);
  wrefresh(window);

  DIR* mapDir;
  struct dirent* file;

  mapDir = opendir("./data/map");

  int counter = 0;

  if (mapDir != NULL) {
    while ((file = readdir(mapDir))) {
      if (std::regex_match(file->d_name, std::regex("(.+)(\\.map)"))) {
        mvwprintw(window, counter++, 0, file->d_name);
      }
    }
  }

  wrefresh(window);

  Game game;
  BackScreen back;

  std::vector<MenuOption> menuOptionList = {
    MenuOption(window, "one", game),
    MenuOption(window, "two", game),
    MenuOption(window, "three", game),
    MenuOption(window, "back to main menu", back)
  };

  MenuHeading heading(window, "Load game");
  heading.print((int) menuOptionList.size());

  usleep(SCREEN_DELAY);

  Menu().process(window, heading, menuOptionList, false);

  return PROCESS_OK;
}
