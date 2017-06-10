#ifndef SEMESTRAL_WORK_MENUSCREEN_HPP
#define SEMESTRAL_WORK_MENUSCREEN_HPP

#include "../menu/MenuHeading.hpp"

#include "Screen.hpp"

/**
 * Displays and process a menu screen and functionality.
 */
class MenuScreen : public Screen {
public:
  int process () const override;

private:
  /**
   * Menu loop functionality - switching options, selection items, ...
   * @param heading menu heading object which we want to redrawing
   */
  void loop (MenuHeading& heading) const;
};

#endif // SEMESTRAL_WORK_MENUSCREEN_HPP
