#ifndef SEMESTRAL_WORK_SCREEN_HPP
#define SEMESTRAL_WORK_SCREEN_HPP

#include <ncurses.h>

#define SCREEN_COLOR_BRIGHT 8

#define SCREEN_OK 1
#define SCREEN_EXIT 2

/**
 * Screen is the abstract class that provides basic console screen unit and functionality.
 */
class Screen {
public:
  /**
   * Constructor initializes the window.
   */
  Screen ();

  /**
   * Destructor, which deletes the window.
   */
  virtual ~Screen ();

  /**
   * Process the screen with its own loop and functionality.
   */
  virtual int process () const = 0; // `= 0` makes this class abstract
protected:
  /**
   * Specific generic window of each Screen object.
   */
  WINDOW* window;
};

#endif // SEMESTRAL_WORK_SCREEN_HPP
