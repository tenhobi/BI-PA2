#ifndef SEMESTRAL_WORK_INFOSCREEN_HPP
#define SEMESTRAL_WORK_INFOSCREEN_HPP

#include <string>

#include "../ColorPairGenerator.hpp"

#include "Screen.hpp"

class InfoScreen: Screen {
public:
  int process () override;

  /**
   * Takes the text of the info and does process.
   *
   * @copydoc process
   */
  int process (std::string text);

  int process (std::string text, int time);

private:
  const short color = ColorPairGenerator::addColor(COLOR_GREEN, 0);
  const short activeColor = ColorPairGenerator::addColor(COLOR_GREEN + SW_COLOR_BRIGHT, 0);
};

#endif // SEMESTRAL_WORK_INFOSCREEN_HPP
