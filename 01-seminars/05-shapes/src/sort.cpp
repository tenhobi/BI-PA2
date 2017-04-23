#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
template <class fn>
void sortx (vector<int> & v, const fn & komparator) {
  cout << "komparator: " << komparator (1, 2) << endl;
  sort(v.begin(), v.end(), komparator);
}
*/

void sortx (vector<int> & v, function<bool(int,int)> komparator) {
  cout << "komparator: " << komparator (1, 2) << endl;
  sort(v.begin(), v.end(), komparator);
}

bool cmp (int a, int b) {
  return a < b;
}

int main () {
  vector<int> v = {1, 5, 6, 7, 1, 8, 3} ;
  sortx(v, cmp);

  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }

  cout << endl;

  sortx(v, [] (int a, int b) {return a > b;});

  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }

  cout << endl;
}
