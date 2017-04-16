#include <string>
#include <iostream>

using namespace std;

class Zamestnanec {
public:
    Zamestnanec (const string& popis, const string& jmeno, int plat) : popis(popis), jmeno(jmeno), plat(plat) {}

    virtual string getPopis () const { return popis; }

    virtual string getJmeno () const { return jmeno; }

    virtual int getPlat () const { return plat; }

    virtual void print (ostream& os) const {
        os << getJmeno() << endl;
        os << getPopis() << endl;
        os << getPlat();
    }

    friend ostream& operator << (ostream& os, const Zamestnanec& z) {
        z.print(os);
        return os;
    }

private:
protected:
    string popis;
    string jmeno;
    int plat;
};

class Reditel : public Zamestnanec {
public:
    Reditel (const string& popis, const string& jmeno, int plat, const string& benefity) : Zamestnanec(popis, jmeno, plat) {
        this->benefity = benefity;
    }

    string getBenefity () const { return benefity; }

    int getPlat () const override { return plat * 3; }

    void print ( ostream& os ) const override {
        os << getJmeno() << endl;
        os << getPopis() << endl;
        os << getPlat() << endl;
        os << getBenefity();
    }

private:
protected:
    string benefity;
};

int main () {
    Zamestnanec z("skladnik Rohlik", "jmeno", 10000);
    Reditel r("reditel Rohliku", "DEF", 15000, "auto");

    Zamestnanec* pole[5];
    pole[0] = new Zamestnanec("p0", "j0", 1000);
    pole[1] = new Zamestnanec("p1", "j1", 1000);
    pole[2] = new Zamestnanec("p2", "j2", 1000);
    pole[3] = new Reditel("p3", "j3", 1000, "auto");
    pole[4] = new Reditel("p4", "j4", 1000, "auto");

    for (int i = 0; i < 5; ++i) {
        cout << *pole[i] << endl;
    }
}
