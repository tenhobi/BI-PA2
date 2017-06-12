#ifndef SEMESTRAL_WORK_INFOSCREEN_HPP
#define SEMESTRAL_WORK_INFOSCREEN_HPP

#include <string>

#include "Screen.hpp"

/**
 * Displays and process an info screen and it's functionality.
 */
class InfoScreen : public Screen {
public:
  /**
   * A constructor.
   */
  InfoScreen ();

  virtual ScreenState process () override;

  /**
   * Takes the text of the info and does process.
   *
   * @copydoc process
   */
  virtual ScreenState process (std::string text);

  /**
   * Prints the delayed window with heading and text.
   *
   * @param text
   * @param time time to wait to any key press in milliseconds, or -1 for infinity time
   *
   * @return
   */
  virtual ScreenState process (std::string text, int time);

protected:
  /**
   * Number of registered ncurses color pair.
   */
  short color;

  /**
   * Name of the info window, e.g. heading.
   */
  std::string headingText;
};

#endif // SEMESTRAL_WORK_INFOSCREEN_HPP
