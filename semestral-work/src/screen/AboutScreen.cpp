#include "AboutScreen.hpp"

// milliseconds
#define SCREEN_DELAY 5000

int AboutScreen::process () const {
  mvwprintw(window, 0,0, "Lorem ipsum dolor sit amet, per amet invenire an, ei natum vitae senserit has. At usu nonumes copiosae, at iuvaret percipitur eos. In duo ignota periculis. At per dolore saperet perfecto, id nemore audire pro, mei nemore fabulas at. Mea eu blandit consequuntur. Feugait reprehendunt ea vix, ut vim autem aperiam verterem.\n\nLorem ipsum dolor sit amet, per amet invenire an, ei natum vitae senserit has. At usu nonumes copiosae, at iuvaret percipitur eos. In duo ignota periculis. At per dolore saperet perfecto, id nemore audire pro, mei nemore fabulas at. Mea eu blandit consequuntur. Feugait reprehendunt ea vix, ut vim autem aperiam verterem.\n\nLorem ipsum dolor sit amet, per amet invenire an.");

  wrefresh(window);

  // Use non blocking read.
  timeout(SCREEN_DELAY);
  getch();

  wclear(window);
  
  return SCREEN_OK;
}
