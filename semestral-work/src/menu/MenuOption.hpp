#ifndef SEMESTRAL_WORK_MENUOPTION_HPP
#define SEMESTRAL_WORK_MENUOPTION_HPP

#include <string>

#include "../screen/Screen.hpp"
#include "../ColorPairGenerator.hpp"

#include "MenuItem.hpp"

class MenuOption : public MenuItem {
public:
  bool active = false;

  MenuOption (WINDOW* window, const std::string text, Screen& screen);

  void print (int offset, bool active) const;

  void print () const override;

  int process () const;

private:
  Screen& screen;

  const short color = ColorPairGenerator::addColor(COLOR_WHITE, 0);
  const short colorActive = ColorPairGenerator::addColor(COLOR_CYAN + SCREEN_COLOR_BRIGHT, 0);
};

#endif // SEMESTRAL_WORK_MENUOPTION_HPP
