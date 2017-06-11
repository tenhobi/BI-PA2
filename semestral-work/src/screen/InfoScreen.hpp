#ifndef SEMESTRAL_WORK_INFOSCREEN_HPP
#define SEMESTRAL_WORK_INFOSCREEN_HPP

#include <string>

#include "Screen.hpp"

class InfoScreen : public Screen {
public:
  InfoScreen ();

  virtual ScreenState process () override;

  /**
   * Takes the text of the info and does process.
   *
   * @copydoc process
   */
  virtual ScreenState process (std::string text);

  /**
   *
   * @param text
   * @param time time to wait to any key press in milliseconds, or -1 for infinity time
   * @return
   */
  virtual ScreenState process (std::string text, int time);

protected:
  short color;
  short activeColor;
  std::string headingText;
};

#endif // SEMESTRAL_WORK_INFOSCREEN_HPP
