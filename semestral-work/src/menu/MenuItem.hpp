#ifndef SEMESTRAL_WORK_MENUITEM_HPP
#define SEMESTRAL_WORK_MENUITEM_HPP

#include <string>

#include "../screen/Screen.hpp"

class MenuItem {
public:
  MenuItem (WINDOW* window, const std::string text);

  virtual void print () const = 0; // `= 0` makes this class abstract

protected:
  WINDOW* window;
  const std::string text;
  const char* ctext;
};

#endif // SEMESTRAL_WORK_MENUITEM_HPP
