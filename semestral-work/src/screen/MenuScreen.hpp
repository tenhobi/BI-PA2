#ifndef SEMESTRAL_WORK_MENUSCREEN_HPP
#define SEMESTRAL_WORK_MENUSCREEN_HPP

#include "../menu/MenuHeading.hpp"

#include "Screen.hpp"

/**
 * Displays and process a menu screen and functionality.
 */
class MenuScreen : public Screen {
public:
  int process () override;
};

#endif // SEMESTRAL_WORK_MENUSCREEN_HPP
