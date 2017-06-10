#ifndef SEMESTRAL_WORK_MENUITEM_HPP
#define SEMESTRAL_WORK_MENUITEM_HPP

#include <string>

#include "../screen/Screen.hpp"

/**
 * This abstract class provides generic interface for menu items.
 */
class MenuItem {
public:
  /**
   * Constructor.
   * @param window ncurses window
   * @param text text of menu item
   */
  MenuItem (WINDOW* window, const std::string text);

  /**
   * Basic function of the menu item, which prints item into the ncurses window.
   */
  virtual void print () const = 0; // `= 0` makes this class abstract

protected:
  /**
   * Ncurses window where the menu item should be printed.
   */
  WINDOW* window;

  /**
   * Text of the menu item as string.
   */
  const std::string text;

  /**
   * Text of the menu item as chars.
   */
  const char* ctext;
};

#endif // SEMESTRAL_WORK_MENUITEM_HPP
