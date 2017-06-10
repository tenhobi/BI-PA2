#include <dirent.h>
#include <iostream>
#include <regex>
#include <unistd.h>

#include "../menu/MenuOption.hpp"
#include "../game/Game.hpp"
#include "../menu/MenuHeading.hpp"
#include "BackScreen.hpp"
#include "../menu/Menu.hpp"

#include "NewGameScreen.hpp"

int NewGameScreen::process () {
  wclear(window);
  wrefresh(window);

  Game game;
  BackScreen back;

  DIR* saveDir;
  struct dirent* file;

  saveDir = opendir("./data/map");

  std::vector<MenuOption> menuOptionList;

  int counter = 0;

  if (saveDir != NULL) {
    while ((file = readdir(saveDir))) {
      if (std::regex_match(file->d_name, std::regex("(.+)(\\.map)"))) {
        mvwprintw(window, counter++, 0, file->d_name);
        menuOptionList.push_back(MenuOption(window, std::string(file->d_name), game));
      }
    }
  }

  closedir(saveDir);

  menuOptionList.push_back(MenuOption(window, "back to main menu", back));

  wrefresh(window);

  MenuHeading heading(window, "Select map template for a new game");
  heading.print((int) menuOptionList.size());

  usleep(SCREEN_DELAY);

  Menu().process(window, heading, menuOptionList, false);

  return PROCESS_OK;
}
