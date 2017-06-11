#ifndef SEMESTRAL_WORK_SCREEN_HPP
#define SEMESTRAL_WORK_SCREEN_HPP

#include <ncurses.h>

#include "../Config.hpp"

#include "../Processable.hpp"

// microseconds
#define SCREEN_DELAY 1000000

/**
 * Abstract class that provides basic console screen unit and it's functionality.
 */
class Screen : public Processable {
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
  virtual int process () override = 0; // `= 0` makes this class abstract
protected:
  /**
   * Generic new window of this screen.
   */
  WINDOW* window;
};

#endif // SEMESTRAL_WORK_SCREEN_HPP
