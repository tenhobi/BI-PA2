#ifndef SEMESTRAL_WORK_EXITSCREEN_HPP
#define SEMESTRAL_WORK_EXITSCREEN_HPP

#include "Screen.hpp"

/**
 * Displays and process an exit screen and functionality.
 */
class ExitScreen : public Screen {
public:
  int process () const override;
};

#endif // SEMESTRAL_WORK_EXITSCREEN_HPP
