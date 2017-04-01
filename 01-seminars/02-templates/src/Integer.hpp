//
// Created by HoBi on 29.03.2017.
//

#ifndef INTEGER_HPP
#define INTEGER_HPP

#include <iostream>

class Integer {
public:
    Integer (int x) : x(x) {};

    Integer operator + (const Integer &b) const;

    friend std::ostream &operator << (std::ostream &os, const Integer &x) {
      os << x.x;
      return os;
    }

    // c++ 11 only
    operator int () const {
      return x;
    }
private:
    int x;
};

#endif //INTEGER_HPP
