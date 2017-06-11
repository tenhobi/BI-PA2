#include <dirent.h>
#include <iostream>
#include <regex>
#include <unistd.h>

#include "../Config.hpp"

#include "../menu/MenuOption.hpp"
#include "../menu/MenuHeading.hpp"
#include "../menu/Menu.hpp"
#include "BackScreen.hpp"
#include "GameScreen.hpp"

#include "LoadGameScreen.hpp"
#include "ErrorScreen.hpp"
#include "AboutScreen.hpp"

int LoadGameScreen::process () {
  wclear(window);
  wrefresh(window);

  DIR* saveDir;
  struct dirent* file;

  saveDir = opendir(SW_GAME_DATA_SAVE);

  std::vector<MenuOption> menuOptionList;

  std::vector<GameScreen> gameScreenList;

  if (saveDir != NULL) {
    while ((file = readdir(saveDir))) {
      if (std::regex_match(file->d_name, std::regex("(.+)(" + std::string(SW_GAME_DATA_EXTENSION_REGEX) +")"))) {
        GameScreen game(std::string(file->d_name));
        gameScreenList.push_back(game);
        menuOptionList.push_back(MenuOption(window, std::string(file->d_name), gameScreenList[(gameScreenList.size() - 1)]));
      }
    }
  }

  closedir(saveDir);

  AboutScreen back;
  menuOptionList.push_back(MenuOption(window, "back to main menu", back));

  wrefresh(window);

  MenuHeading heading(window, "Select a game file to load");
  heading.print((int) menuOptionList.size());

  Menu().process(window, heading, menuOptionList, false);

  return PROCESS_OK;
}
