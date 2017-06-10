#ifndef SEMESTRAL_WORK_MENUSCREEN_HPP
#define SEMESTRAL_WORK_MENUSCREEN_HPP

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
   */
  void loop () const;
};

#endif // SEMESTRAL_WORK_MENUSCREEN_HPP
