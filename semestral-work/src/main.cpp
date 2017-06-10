#include <ncurses.h>

#include "screen/MenuScreen.hpp"

int main (int argc, char* argv[]) {
  // Initialize the terminal data.
  initscr();

  // Disable cursor.
  noecho();
  curs_set(FALSE);

  // Enable text and background colors.
  start_color();

  // Gets keyboard input.
  keypad(stdscr, TRUE);

  refresh();

  MenuScreen().process();

  // End the default window.
  endwin();
}
