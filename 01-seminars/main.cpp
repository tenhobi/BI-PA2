#include <iostream>
#include "bag.h"

using namespace std;

int main () {
    Bag b1;
    b1.vloz(1);
    b1.vloz(3);
    b1.vloz(1);
    b1.vloz(2);

    cout << "b1 = " << b1 << endl;

    Bag b2 = b1;
    b1.odeber(1);

    cout << "b1 = " << b1 << endl;
    cout << "b2 = " << b2 << endl;

    Bag b3;
    b3 = b1;
    b1.odeber(1);

    cout << "b1 = " << b1 << endl;
    cout << "b3 = " << b3 << endl;

    b3 = b3;

    cout << "b3 = " << b3 << endl;

    return 0;
}