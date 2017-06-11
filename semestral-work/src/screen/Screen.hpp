#ifndef SEMESTRAL_WORK_SCREEN_HPP
#define SEMESTRAL_WORK_SCREEN_HPP

#include <ncurses.h>

#include "../Config.hpp"

#define SCREEN_OK 1
#define SCREEN_EXIT 2
#define SCREEN_BACK 3
#define SCREEN_INPUT_ERROR 4

// microseconds
#define SCREEN_DELAY 1000000

/**
 * Provides basic console screen unit and it's functionality.
 */
class Screen {
public:
  /**
   * Constructor initializes the ncurses window.
   */
  Screen ();

  /**
   * Virtual destructor destroying the ncurses window.
   */
  virtual ~Screen ();

  /**
   * Processes the screen purpose, loops etc.
   *
   * @return process status code.
   */
  virtual int process ();
protected:
  /**
   * Generic new window of this screen.
   */
  WINDOW* window;
};

#endif // SEMESTRAL_WORK_SCREEN_HPP
