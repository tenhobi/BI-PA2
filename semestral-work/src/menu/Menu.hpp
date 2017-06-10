#ifndef SEMESTRAL_WORK_MENU_HPP
#define SEMESTRAL_WORK_MENU_HPP

#include <vector>

#include "../Processable.hpp"

#include "MenuOption.hpp"

class Menu {
public:
  void process (WINDOW* window, MenuHeading heading, std::vector<MenuOption> items, bool exit);
};

#endif // SEMESTRAL_WORK_MENU_HPP
