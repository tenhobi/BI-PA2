#ifndef SEMESTRAL_WORK_ROAD_HPP
#define SEMESTRAL_WORK_ROAD_HPP

#include "Cell.hpp"

class Road : public Cell {
public:
    Road (bool startingEdge, bool finalEdge);
    Road* next;
private:
    bool startingEdge;
    bool finalEdge;
};

#endif // SEMESTRAL_WORK_ROAD_HPP
