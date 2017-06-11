#ifndef SEMESTRAL_WORK_MENUOPTION_HPP
#define SEMESTRAL_WORK_MENUOPTION_HPP

#include <ncurses.h>
#include <string>

#include "../screen/Screen.hpp"
#include "../ColorPairGenerator.hpp"
#include "../Config.hpp"
#include "../screen/Screen.hpp"
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
   *
   * @param window ncurses window to work with
   * @param text text of the item
   * @param screen screen to process when this item is selected
   */
  MenuOption (WINDOW* window, const std::string text, Screen* screen);

  void print (int numberOfItem) const override;

  /**
   * Special item printing function for the menu option item.
   *
   * @param numberOfItems number of items for object to know where to print itself
   * @param offset y axis offset to print
   * @param active state of the item
   */
  void print (int numberOfItems, int offset, bool active) const;

  /**
   * Processes the linked process.
   *
   * @return process's process return code.
   */
  int process ();

protected:
  /**
   * Screen to process when the this menu option item is selected.
   */
  Screen* screen;

  /**
   * Color of the item.
   */
  const short color = ColorPairGenerator::addColor(COLOR_WHITE, 0);

  /**
   * Color of the active item.
   */
  const short colorActive = ColorPairGenerator::addColor(COLOR_CYAN, 0);
};

#endif // SEMESTRAL_WORK_MENUOPTION_HPP
