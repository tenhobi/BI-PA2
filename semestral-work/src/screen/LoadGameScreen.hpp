#ifndef SEMESTRAL_WORK_LOADGAMESCREEN_HPP
#define SEMESTRAL_WORK_LOADGAMESCREEN_HPP

#include "Screen.hpp"

/**
 * Displays and process a load game screen and it's functionality.
 */
class LoadGameScreen : public Screen {
public:
  ScreenState process () override;
};

#endif // SEMESTRAL_WORK_LOADGAMESCREEN_HPP
