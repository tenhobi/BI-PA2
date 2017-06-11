#include <ncurses.h>
#include <string>

#include "MenuItem.hpp"

MenuItem::MenuItem (WINDOW* window, const std::string text) : window(window), text(text), ctext(text.c_str()) {}

MenuItem::~MenuItem () {}
