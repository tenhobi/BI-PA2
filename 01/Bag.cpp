#include "Bag.h"
#include <algorithm>

Bag::Bag () {
    cnt = 0;
    size = 5;
    data = new int[size];
}

Bag::Bag (const Bag &b) {
    cnt = b.cnt;
    size = b.size;
    // data = b.data;
    data = new int[size];
    for (int i = 0; i < cnt; ++i) {
        data[i] = b.data[i];
    }
}

Bag::~Bag () {
    delete[] data;
}

void Bag::vloz (int x) {
    if (cnt == size) {
        int *tmp = new int[size *= 2];

        for (int i = 0; i < cnt; ++i) {
            tmp[i] = data[i];
        }

        delete[] data;
        data = tmp;
    }

    data[cnt++] = x;
}

bool Bag::odeber (int x) {
    for (int i = 0; i < cnt; ++i) {
        if (x == data[i]) {
            cnt--;

            for (int j = i; j < cnt; ++j) {
                data[j] = data[j + 1];
            }

            return true;
        }
    }

    return false;
}

bool Bag::jeTam (int x) const {
    for (int i = 0; i < cnt; ++i) {
        if (x == data[i]) {
            return true;
        }
    }

    return false;
}

Bag &Bag::operator= (const Bag &b) {
    if (this == &b) {
        return *this;
    }

    delete[] data;

    /*
    cnt = b.cnt;
    size = b.size;
    data = new int[size];

    for (int i = 0; i < cnt; ++i) {
        data[i] = b.data[i];
    }
    */

    Bag tmp(b);

    std::swap(cnt, tmp.cnt);
    std::swap(size, tmp.size);
    std::swap(data, tmp.data);

    return *this;
}

std::ostream &operator<< (std::ostream &os, const Bag &b) {
    os << "Bag:";

    for (int i = 0; i < b.cnt; ++i) {
        os << " " << b.data[i];
    }

    return os;
}
