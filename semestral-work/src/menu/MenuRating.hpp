#ifndef SEMESTRAL_WORK_MENURATING_HPP
#define SEMESTRAL_WORK_MENURATING_HPP

#include <string>
#include <ncurses.h>

#include "MenuItem.hpp"

class MenuRating: public MenuItem {
public:
  MenuRating (WINDOW* window, const std::string text);

  void print () const override;
};

#endif // SEMESTRAL_WORK_MENURATING_HPP
