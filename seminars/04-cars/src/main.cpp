#include <string>
#include <iostream>

using namespace std;

class Vozidlo {
public:
    Vozidlo (int kapacita, int spotreba) : kapacita(kapacita), spotreba(spotreba) {}

    virtual ~Vozidlo () {}

    virtual void print (ostream& os) const {
        os << kapacita << " --- " << spotreba << endl;
    }

protected:
    int kapacita;
    int spotreba;
};

class Autobus : public Vozidlo {
public:
    Autobus (int kapacita, int spotreba, string cislo) : Vozidlo(kapacita, spotreba), cislo(cislo) {
        a = new char[100];
    }

    ~Autobus () { delete[] a; }

    virtual void print (ostream& os) const override {
        os << kapacita << " ... " << spotreba << " " << endl;
    }

public:
    char* a;
protected:
    string cislo;
};

class Auto : public Vozidlo {
public:
    Auto (int kapacita, int spotreba) : Vozidlo(kapacita, spotreba) {}
};

int main () {
    Vozidlo** pole = new Vozidlo* [5];
    pole[0] = new Vozidlo(6, 6);
    pole[1] = new Vozidlo(6, 8);
    pole[2] = new Auto(6, 6);
    pole[3] = new Auto(6, 10);
    pole[4] = new Autobus(66, 6, "ccc");

    for (int i = 0; i < 5; ++i) {
        pole[i]->print(cout);
    }

    for (int i = 0; i < 5; ++i) {
        delete pole[i];
    }

    delete[] pole;

    return 0;
}
