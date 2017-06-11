#ifndef SEMESTRAL_WORK_BACKSCREEN_HPP
#define SEMESTRAL_WORK_BACKSCREEN_HPP

#include "Screen.hpp"

/**
 * Displays and process a back screen and it's functionality.
 */
class BackScreen : public Screen {
public:
  /**
   * A constructor.
   *
   * @param exit determines the return code
   */
  BackScreen (bool exit);

  ScreenState process () override;

private:
  /**
   * Determines if back means exit from screen loop.
   */
  bool exit = false;
};

#endif // SEMESTRAL_WORK_BACKSCREEN_HPP
