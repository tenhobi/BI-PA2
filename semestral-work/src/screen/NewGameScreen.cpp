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

#include "NewGameScreen.hpp"

int NewGameScreen::process () {
  wclear(window);
  wrefresh(window);

  DIR* saveDir;
  struct dirent* file;

  // opens directory
  saveDir = opendir(SW_GAME_DATA_TEMPLATE);

  std::vector<MenuOption> menuOptionList;
  std::vector<GameScreen*> gameScreenList;

  if (saveDir != NULL) {
    // loop through files
    while ((file = readdir(saveDir))) {
      if (std::regex_match(file->d_name, std::regex("(.+)(" + std::string(SW_GAME_DATA_EXTENSION_REGEX) + ")"))) {
        GameScreen* gameScreen = new GameScreen(std::string(file->d_name));
        gameScreenList.push_back(gameScreen);

        menuOptionList.push_back(
          MenuOption(window, std::string(file->d_name), gameScreen)
        );
      }
    }
  }

  closedir(saveDir);

  BackScreen* backScreen = new BackScreen(true);

  menuOptionList.push_back(
    MenuOption(window, "back to main menu", backScreen)
  );

  wrefresh(window);

  MenuHeading heading(window, "Select a game file to create a new game");
  heading.print((int) menuOptionList.size());

  Menu().process(window, heading, menuOptionList);

  delete backScreen;

  for (int i = 0; i < (int) gameScreenList.size(); ++i) {
    delete gameScreenList[i];
  }

  return SCREEN_OK;
}
