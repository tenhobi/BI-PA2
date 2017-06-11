#include <dirent.h>
#include <iostream>
#include <regex>
#include <unistd.h>

#include "../Config.hpp"

#include "../game/Game.hpp"
#include "../menu/MenuHeading.hpp"
#include "BackScreen.hpp"
#include "../menu/MenuOption.hpp"
#include "../menu/Menu.hpp"

#include "LoadGameScreen.hpp"

int LoadGameScreen::process () {
  wclear(window);
  wrefresh(window);

  DIR* saveDir;
  struct dirent* file;

  saveDir = opendir(SW_GAME_DATA_SAVE);

  std::vector<MenuOption> menuOptionList;

  if (saveDir != NULL) {
    while ((file = readdir(saveDir))) {
      if (std::regex_match(file->d_name, std::regex("(.+)(" + std::string(SW_GAME_DATA_EXTENSION_REGEX) +")"))) {
        Game game(std::string(file->d_name));
        menuOptionList.push_back(MenuOption(window, std::string(file->d_name), game));
      }
    }
  }

  closedir(saveDir);

  BackScreen back;
  menuOptionList.push_back(MenuOption(window, "back to main menu", back));

  wrefresh(window);

  MenuHeading heading(window, "Select a game file to load");
  heading.print((int) menuOptionList.size());

  usleep(SCREEN_DELAY);

  Menu().process(window, heading, menuOptionList, false);

  return PROCESS_OK;
}
