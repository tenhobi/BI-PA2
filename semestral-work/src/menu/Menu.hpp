#ifndef SEMESTRAL_WORK_MENU_HPP
#define SEMESTRAL_WORK_MENU_HPP

#include <vector>
#include <ncurses.h>

#include "MenuHeading.hpp"
#include "MenuOption.hpp"

/**
 * Menu wrapper that auto center all items, heading etc.
 */
class Menu {
public:
  /**
   * Processes the build and print process of menu items.
   *
   * @param window ncurses window to print
   * @param heading heading item
   * @param items menu options list
   * @param exit determines the main menu which exits the app
   */
  void process (WINDOW* window, MenuHeading heading, std::vector<MenuOption>& items, bool exit);
};

#endif // SEMESTRAL_WORK_MENU_HPP
