#include <iostream>
#include "screen/MenuScreen.hpp"

int main () {
  MenuScreen menu = MenuScreen();

  std::cout << "Hello, World! " << menu.getSize() << std::endl;
  return 0;
}
