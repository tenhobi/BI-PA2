#ifndef SEMESTRAL_WORK_MENUHEADING_HPP
#define SEMESTRAL_WORK_MENUHEADING_HPP

#include <ncurses.h>
#include <string>

#include "../ColorPairGenerator.hpp"
#include "../Config.hpp"

#include "MenuItem.hpp"

/**
 * Menu heading class, which has the active style.
 */
class MenuHeading : public MenuItem {
public:
  /**
   * Constructor.
   *
   * @param window ncurses window to work with
   * @param text text of the item
   */
  MenuHeading (WINDOW* window, const std::string text);

  void print (int numberOfItems) const override;

  /**
   * Activates the heading styles.
   */

  /**
   * Print of active heading with relative position.
   *
   * @param numberOfItems
   */
  void activePrint (int numberOfItems);

protected:
  /**
   * Determines if the heading is activeted or not.
   */
  bool active = false;

  /**
   * Color of the heading.
   */
  short color = ColorPairGenerator::addColor(COLOR_MAGENTA, 0);

  /**
   * Color of the active heading.
   */
  short activeColor = ColorPairGenerator::addColor(COLOR_YELLOW, 0);
};

#endif // SEMESTRAL_WORK_MENUHEADING_HPP
