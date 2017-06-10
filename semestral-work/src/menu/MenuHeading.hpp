#ifndef SEMESTRAL_WORK_MENUHEADING_HPP
#define SEMESTRAL_WORK_MENUHEADING_HPP

#include "../ColorPairGenerator.hpp"

#include "MenuItem.hpp"

class MenuHeading : public MenuItem {
public:
  MenuHeading (WINDOW* window, const std::string text);

  void print () const override;

  void activate ();

private:
  bool active = false;

  const short color = ColorPairGenerator::addColor(COLOR_YELLOW, 0);
  const short colorActive = ColorPairGenerator::addColor(COLOR_YELLOW + SCREEN_COLOR_BRIGHT, 0);
};

#endif // SEMESTRAL_WORK_MENUHEADING_HPP
