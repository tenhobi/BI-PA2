#ifndef SEMESTRAL_WORK_ERRORSCREEN_HPP
#define SEMESTRAL_WORK_ERRORSCREEN_HPP

#include <string>
#include <ncurses.h>

#include "../Config.hpp"
#include "../ColorPairGenerator.hpp"

#include "Screen.hpp"

/**
 * Displays and process an error screen and it's functionality.
 */
class ErrorScreen : public Screen {
public:
  int process () override;

  /**
   * Takes the text of the error and does process.
   *
   * @copydoc process
   */
  int process (std::string text);

private:
  const short color = ColorPairGenerator::addColor(COLOR_RED, 0);
  const short activeColor = ColorPairGenerator::addColor(COLOR_RED + SW_COLOR_BRIGHT, 0);
};

#endif // SEMESTRAL_WORK_ERRORSCREEN_HPP
