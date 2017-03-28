#include <iostream>

template<typename T>
void print (T arr, int len) {
  for (int i = 0; i < len; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

class Integer {
public:
    Integer (int x) : x(x) {};

    Integer operator + (const Integer &b) const {
      return Integer(x + b.x);
    }

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

template<class T>
T sum (const T &a, const T &b) {
  return a + b;
}

int main () {

  std::cout << sum(1, 2) << std::endl;
  std::cout << sum<int>('A', '2') << std::endl;
  std::cout << sum(Integer(3), Integer(5)) << std::endl;

  return 0;
}
