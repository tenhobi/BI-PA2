#ifndef SEMESTRAL_WORK_MENUOPTION_HPP
#define SEMESTRAL_WORK_MENUOPTION_HPP

#include <string>

#include "../screen/Screen.hpp"
#include "../ColorPairGenerator.hpp"

#include "MenuItem.hpp"

/**
 * Menu option class, which has the active item.
 */
class MenuOption : public MenuItem {
public:
  /**
   * Determines if the this item is active or not.
   */
  bool active = false;

  /**
   * Constructor.
   * @param window ncurses window to work with
   * @param text text of the item
   * @param screen screen to process when this item is selected
   */
  MenuOption (WINDOW* window, const std::string text, Screen& screen);

  /**
   * Special item printing function for the menu option item.
   */
  void print (int offset, bool active) const;

  /**
   * Prints item into the ncurses window with default settings.
   */
  void print () const override;

  /**
   * Processes the linked screen.
   * @return screen's process return code.
   */
  int process () const;

private:
  /**
   * Screen to process when the this menu option item is selected.
   */
  Screen& screen;

  /**
   * Color of the item.
   */
  const short color = ColorPairGenerator::addColor(COLOR_WHITE, 0);

  /**
   * Color of the active item.
   */
  const short colorActive = ColorPairGenerator::addColor(COLOR_CYAN + SCREEN_COLOR_BRIGHT, 0);
};

#endif // SEMESTRAL_WORK_MENUOPTION_HPP
