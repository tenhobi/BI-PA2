#ifndef SEMESTRAL_WORK_MENUSCREEN_HPP
#define SEMESTRAL_WORK_MENUSCREEN_HPP

#include "Screen.hpp"

/**
 * Displays and process a menu screen and it's functionality.
 */
class MenuScreen : public Screen {
public:
  ScreenState process () override;
};

#endif // SEMESTRAL_WORK_MENUSCREEN_HPP
