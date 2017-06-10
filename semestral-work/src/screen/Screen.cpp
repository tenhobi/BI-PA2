#include <ncurses.h>
#include "Screen.hpp"

Screen::Screen () : window(newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0)) {}
