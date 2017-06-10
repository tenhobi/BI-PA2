#ifndef SEMESTRAL_WORK_MENURATING_HPP
#define SEMESTRAL_WORK_MENURATING_HPP

#include <string>
#include <ncurses.h>

#include "MenuItem.hpp"

/**
 * Menu rating class, which displays the rating of the game.
 */
class MenuRating : public MenuItem {
public:
  /**
   * Constructor.
   * @param window ncurses window to work with
   * @param text text of the item
   */
  MenuRating (WINDOW* window, const std::string text);

  void print (int numberOfItems) const override;
};

#endif // SEMESTRAL_WORK_MENURATING_HPP
