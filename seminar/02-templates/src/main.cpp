#include <iostream>
#include "Integer.hpp"

template<typename T>
void print (T arr, int len) {
  for (int i = 0; i < len; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

template<class T>
T sum (const T &a, const T &b) {
  return a + b;
}

int main () {

  std::cout << sum(1, 2) << std::endl;
  std::cout << sum<int>('A', '2') << std::endl;
  std::cout << sum(Integer(3), Integer(11)) << std::endl;

  return 0;
}
