#ifndef INC_01_BAG_H
#define INC_01_BAG_H

#include <ostream>

class Bag {
public:
    Bag ();
    Bag (const Bag &b);
    void aa ();
    void bb ();
    void cc ();
    ~Bag ();
    void vloz (int x);
    bool odeber (int x);
    bool jeTam (int x) const;
    Bag &operator = (const Bag &b);
    friend std::ostream &operator << (std::ostream &os, const Bag &b);

private:
    int *data;
    int cnt;
    int size;
};

#endif //INC_01_BAG_H
