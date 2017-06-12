#include <vector>

#include "Map.hpp"

Map::Map (int height, int width) : height(height), width(width) {}

void Map::resize () {
  // resize 2D map data
  data.resize((unsigned long) height, std::vector<Cell*>((unsigned long) width));
}

Map::~Map () {
  for (int i = 0; i < (int) data.size(); ++i) {
    for (int j = 0; j < (int) data[i].size(); ++j) {
      delete data[i][j];
    }
  }
}
