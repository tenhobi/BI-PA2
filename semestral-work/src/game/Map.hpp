#ifndef SEMESTRAL_WORK_MAP_HPP
#define SEMESTRAL_WORK_MAP_HPP

#include "cell/Cell.hpp"
#include <vector>

class Map {
public:
  std::vector<std::vector<Cell>> data;

  bool load ();

  bool save () const;

  bool init ();

  int getWidth () const;

  int getHeight () const;

  operator bool () const;

private:
  int width;
  int height;
};

#endif // SEMESTRAL_WORK_MAP_HPP
