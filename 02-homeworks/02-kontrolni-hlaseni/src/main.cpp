#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

#endif /* __PROGTEST__ */

class CVATRegister {
public:
    CVATRegister (void);
    ~CVATRegister (void);
    bool NewCompany (const string &name, const string &addr, const string &taxID);
    bool CancelCompany (const string &name, const string &addr);
    bool CancelCompany (const string &taxID);
    bool Invoice (const string &taxID, unsigned int amount);
    bool Invoice (const string &name, const string &addr, unsigned int amount);
    bool Audit (const string &name, const string &addr, unsigned int &sumIncome) const;
    bool Audit (const string &taxID, unsigned int &sumIncome) const;
    unsigned int MedianInvoice (void) const;
private:
    // todo
};

CVATRegister::CVATRegister (void) {

}

CVATRegister::~CVATRegister (void) {

}

bool CVATRegister::NewCompany (const string &name, const string &addr, const string &taxID) {
    return false;
}

bool CVATRegister::CancelCompany (const string &name, const string &addr) {
    return false;
}

bool CVATRegister::CancelCompany (const string &taxID) {
    return false;
}

bool CVATRegister::Invoice (const string &taxID, unsigned int amount) {
    return false;
}

bool CVATRegister::Invoice (const string &name, const string &addr, unsigned int amount) {
    return false;
}

bool CVATRegister::Audit (const string &name, const string &addr, unsigned int &sumIncome) const {
    return false;
}

bool CVATRegister::Audit (const string &taxID, unsigned int &sumIncome) const {
    return false;
}

unsigned int CVATRegister::MedianInvoice (void) const {
    return 0;
}

#ifndef __PROGTEST__

int main (void) {
    unsigned int sumIncome;

    return 0;

    CVATRegister b1;
    assert (b1.NewCompany("ACME", "Kolejni", "666/666/666"));
    assert (b1.NewCompany("ACME", "Thakurova", "666/666"));
    assert (b1.NewCompany("Dummy", "Thakurova", "123456"));
    assert (b1.Invoice("666/666", 2000));
    assert (b1.MedianInvoice() == 2000);
    assert (b1.Invoice("666/666/666", 3000));
    assert (b1.MedianInvoice() == 3000);
    assert (b1.Invoice("123456", 4000));
    assert (b1.MedianInvoice() == 3000);
    assert (b1.Invoice("aCmE", "Kolejni", 5000));
    assert (b1.MedianInvoice() == 4000);
    assert (b1.Audit("ACME", "Kolejni", sumIncome) && sumIncome == 8000);
    assert (b1.Audit("123456", sumIncome) && sumIncome == 4000);
    assert (b1.CancelCompany("ACME", "KoLeJnI"));
    assert (b1.MedianInvoice() == 4000);
    assert (b1.CancelCompany("666/666"));
    assert (b1.MedianInvoice() == 4000);
    assert (b1.Invoice("123456", 100));
    assert (b1.MedianInvoice() == 3000);
    assert (b1.Invoice("123456", 300));
    assert (b1.MedianInvoice() == 3000);
    assert (b1.Invoice("123456", 200));
    assert (b1.MedianInvoice() == 2000);
    assert (b1.Invoice("123456", 230));
    assert (b1.MedianInvoice() == 2000);
    assert (b1.Invoice("123456", 830));
    assert (b1.MedianInvoice() == 830);
    assert (b1.Invoice("123456", 1830));
    assert (b1.MedianInvoice() == 1830);
    assert (b1.Invoice("123456", 2830));
    assert (b1.MedianInvoice() == 1830);
    assert (b1.Invoice("123456", 2830));
    assert (b1.MedianInvoice() == 2000);
    assert (b1.Invoice("123456", 3200));
    assert (b1.MedianInvoice() == 2000);

    CVATRegister b2;
    assert (b2.NewCompany("ACME", "Kolejni", "abcdef"));
    assert (b2.NewCompany("Dummy", "Kolejni", "123456"));
    assert (!b2.NewCompany("AcMe", "kOlEjNi", "1234"));
    assert (b2.NewCompany("Dummy", "Thakurova", "ABCDEF"));
    assert (b2.MedianInvoice() == 0);
    assert (b2.Invoice("ABCDEF", 1000));
    assert (b2.MedianInvoice() == 1000);
    assert (b2.Invoice("abcdef", 2000));
    assert (b2.MedianInvoice() == 2000);
    assert (b2.Invoice("aCMe", "kOlEjNi", 3000));
    assert (b2.MedianInvoice() == 2000);
    assert (!b2.Invoice("1234567", 100));
    assert (!b2.Invoice("ACE", "Kolejni", 100));
    assert (!b2.Invoice("ACME", "Thakurova", 100));
    assert (!b2.Audit("1234567", sumIncome));
    assert (!b2.Audit("ACE", "Kolejni", sumIncome));
    assert (!b2.Audit("ACME", "Thakurova", sumIncome));
    assert (!b2.CancelCompany("1234567"));
    assert (!b2.CancelCompany("ACE", "Kolejni"));
    assert (!b2.CancelCompany("ACME", "Thakurova"));
    assert (b2.CancelCompany("abcdef"));
    assert (b2.MedianInvoice() == 2000);
    assert (!b2.CancelCompany("abcdef"));
    assert (b2.NewCompany("ACME", "Kolejni", "abcdef"));
    assert (b2.CancelCompany("ACME", "Kolejni"));
    assert (!b2.CancelCompany("ACME", "Kolejni"));

    return 0;
}

#endif /* __PROGTEST__ */
