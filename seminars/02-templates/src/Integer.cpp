#include "Integer.hpp"

Integer Integer::operator + (const Integer &b) const {
    return Integer(x + b.x);
}
