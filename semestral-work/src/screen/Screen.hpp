#ifndef SEMESTRAL_WORK_SCREEN_HPP
#define SEMESTRAL_WORK_SCREEN_HPP

#include <ncurses.h>

#include "../Processable.hpp"

#define SCREEN_COLOR_BRIGHT 8

// For some odd reason the KEY_ENTER is not the enter key. This should be the enter key code.
#define REAL_ENTER_KEY 10

// microseconds
#define SCREEN_DELAY 1000000

/**
 * Screen is the abstract class that provides basic console screen unit and functionality.
 */
class Screen : public Processable {
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
  virtual int process () override = 0; // `= 0` makes this class abstract
protected:
  /**
   * Specific generic window of each Screen object.
   */
  WINDOW* window;
};

#endif // SEMESTRAL_WORK_SCREEN_HPP
