#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;

class CDate {
public:
    //---------------------------------------------------------------------------------------------
    CDate (int y, int m, int d) : m_Year(y), m_Month(m), m_Day(d) {
    }

    //---------------------------------------------------------------------------------------------
    int Compare (const CDate& x) const {
        if (m_Year != x.m_Year)
            return m_Year - x.m_Year;
        if (m_Month != x.m_Month)
            return m_Month - x.m_Month;
        return m_Day - x.m_Day;
    }

    //---------------------------------------------------------------------------------------------
    int Year (void) const {
        return m_Year;
    }

    //---------------------------------------------------------------------------------------------
    int Month (void) const {
        return m_Month;
    }

    //---------------------------------------------------------------------------------------------
    int Day (void) const {
        return m_Day;
    }

    //---------------------------------------------------------------------------------------------
    friend ostream& operator << (ostream& os,
                                 const CDate& x) {
        char oldFill = os.fill();
        return os << setfill('0') << setw(4) << x.m_Year << "-"
                  << setw(2) << (int) x.m_Month << "-"
                  << setw(2) << (int) x.m_Day
                  << setfill(oldFill);
    }
    //---------------------------------------------------------------------------------------------
private:
    int16_t m_Year;
    int8_t m_Month;
    int8_t m_Day;
};

#endif /* __PROGTEST__ */

string NormalizeName (const string& name) {
    string normalized = "";

    bool space = false;
    bool start = true;

    for (unsigned int i = 0; i < name.size(); ++i) {
        if (name[i] == ' ') {
            space = true;
            continue;
        } else if (name[i] >= 'A' && name[i] <= 'Z') {
            if (space) {
                if (start) {
                    normalized += (name[i] + ('a' - 'A'));
                    start = false;
                    space = false;
                    continue;
                }

                normalized += ' ';
                space = false;
            }

            normalized += (name[i] + ('a' - 'A'));
            continue;
        }

        if (space) {
            if (start) {
                normalized += name[i];
                start = false;
                space = false;
                continue;
            }

            normalized += ' ';
            space = false;
        }

        normalized += name[i];
        start = false;
    }

    return normalized;
}

class CInvoice {
public:
    CInvoice (const CDate& date, const string& seller, const string& buyer, unsigned int amount, double VAT) : m_Date(date), m_Seller(seller), m_Buyer(buyer), m_Amount(amount),
                                                                                                               m_VAT(VAT) {
        m_NormBuyer = NormalizeName(m_Buyer);
        m_NormSeller = NormalizeName(m_Seller);
    }

    bool isIssued = false;
    bool isAccepted = false;

    CDate Date (void) const {
        return m_Date;
    }

    string Buyer (void) const {
        return m_Buyer;
    }

    string NormBuyer (void) const {
        return m_Buyer;
    }

    string Seller (void) const {
        return m_Seller;
    }

    string NormSeller (void) const {
        return m_Seller;
    }

    int Amount (void) const {
        return m_Amount;
    }

    double VAT (void) const {
        return m_VAT;
    }

private:
    CDate m_Date;
    string m_Seller;
    string m_NormSeller;
    string m_Buyer;
    string m_NormBuyer;
    unsigned int m_Amount;
    double m_VAT;
};

class CCompany {
public:
    CCompany (const string& name) : m_Name(name) {}

//    friend ostream& operator << (ostream& os, const CCompany& c) {
//        os << c.m_Name;
//        return os;
//    }

    unordered_map<string, CInvoice> invoices;

private:
    string m_Name;
};

class CSortOpt {
public:
    static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;

    CSortOpt (void) {}

    CSortOpt& AddKey (int key, bool ascending = true) {
        keyList.push_back({key, ascending});
        return *this;
    }
    vector<pair<int, bool>> keyList;
private:

};

struct CompareInvoice {
public:
    static const int LESS = 0;
    static const int EQUAL = 1;
    static const int MORE = 2;
    CompareInvoice(const CSortOpt& sortBy): sortKeys(sortBy) {}

    bool operator () (const CInvoice& a, const CInvoice& b) {
        for (auto& x: sortKeys.keyList) {
//            cout << x.first << " " << x.second << endl;
            switch (x.first) {
                case CSortOpt::BY_DATE:
                    if (x.second ? (a.Date().Compare(b.Date()) < 0) : (b.Date().Compare(a.Date()) < 0)) {
                        return true;
                    } else if (a.Date().Compare(b.Date()) == 0) {
                        continue;
                    }

                    break;
                case CSortOpt::BY_BUYER:
                    if (x.second ? (a.NormBuyer() < b.NormBuyer()) : (b.NormBuyer() < a.NormBuyer())) {
                        return true;
                    } else if (a.NormBuyer() == b.NormBuyer()) {
                        continue;
                    }

                    break;
                case CSortOpt::BY_SELLER:
                    if (x.second ? (a.NormSeller() < b.NormSeller()) : (b.NormSeller() < a.NormSeller())) {
                        return true;
                    } else if (a.NormSeller() == b.NormSeller()) {
                        continue;
                    }

                    break;
                case CSortOpt::BY_AMOUNT:
                    if (x.second ? (a.Amount() < b.Amount()) : (b.Amount() < a.Amount())) {
                        return CompareInvoice::LESS;
                    } else if (a.Amount() == b.Amount()) {
                        return CompareInvoice::EQUAL;
                    }
                    break;
                case CSortOpt::BY_VAT:
                    if (x.second ? (a.VAT() < b.VAT()) : (b.VAT() < a.VAT())) {
                        return CompareInvoice::LESS;
                    } else if (a.VAT() == b.VAT()) {
                        return CompareInvoice::EQUAL;
                    }
                    break;
                default:
                    break;
            }
        }

        return false;
    }
private:
    CSortOpt sortKeys;

};

class CVATRegister {
public:
    CVATRegister (void) {

    }

    bool RegisterCompany (const string& name) {

        string normalizedName = NormalizeName(name);

        if (companies.count(normalizedName) == 0) {
            companies.insert({normalizedName, CCompany(name)});
            return true;
        }

        return false;
    }

    bool AddIssued (const CInvoice& x) {
        string buyerName = NormalizeName(x.Buyer());
        string sellerName = NormalizeName(x.Seller());

        if (companies.count(buyerName) == 0 || companies.count(sellerName) == 0 || buyerName == sellerName) {
            return false;
        }

        string key = NormalizeName(x.Buyer()) + "_" +
                     NormalizeName(x.Seller()) + "_" +
                     to_string(x.Date().Year()) + "_" +
                     to_string(x.Date().Month()) + "_" +
                     to_string(x.Date().Day()) + "_" +
                     to_string(x.Amount()) + "_" +
                     to_string(x.VAT());

        if (companies.at(sellerName).invoices.count(key) == 0 ||
            (companies.at(sellerName).invoices.count(key) == 1 && !companies.at(sellerName).invoices.at(key).isIssued)) {
            companies.at(sellerName).invoices.insert({key, x});
            companies.at(sellerName).invoices.at(key).isIssued = true;
            companies.at(buyerName).invoices.insert({key, x});
            companies.at(buyerName).invoices.at(key).isIssued = true;
            return true;
        }

        return false;
    }

    bool AddAccepted (const CInvoice& x) {
        string buyerName = NormalizeName(x.Buyer());
        string sellerName = NormalizeName(x.Seller());

        if (companies.count(buyerName) == 0 || companies.count(sellerName) == 0 || buyerName == sellerName) {
            return false;
        }

        string key = NormalizeName(x.Buyer()) + "_" +
                     NormalizeName(x.Seller()) + "_" +
                     to_string(x.Date().Year()) + "_" +
                     to_string(x.Date().Month()) + "_" +
                     to_string(x.Date().Day()) + "_" +
                     to_string(x.Amount()) + "_" +
                     to_string(x.VAT());

        if (companies.at(sellerName).invoices.count(key) == 0 ||
            (companies.at(sellerName).invoices.count(key) == 1 && !companies.at(sellerName).invoices.at(key).isAccepted)) {
            companies.at(sellerName).invoices.insert({key, x});
            companies.at(sellerName).invoices.at(key).isAccepted = true;
            companies.at(buyerName).invoices.insert({key, x});
            companies.at(buyerName).invoices.at(key).isAccepted = true;
            return true;
        }

        return false;
    }

    bool DelIssued (const CInvoice& x) {
        return false;
    }

    bool DelAccepted (const CInvoice& x) {
        return false;
    }

    list<CInvoice> Unmatched (const string& company, const CSortOpt& sortBy) const {
        list<CInvoice> sortedInvoicesList;
        string companyName = NormalizeName(company);

        if (companies.count(NormalizeName(company)) == 0) {
            return sortedInvoicesList;
        }

//        cout << " ---- " << endl;

        for (auto x : companies.at(companyName).invoices) {
            if (companies.at(companyName).accepted.count(x.first) == 0) {
                sortedInvoicesList.push_back(x.second);
//                cout << "__ " <<  x.second.Seller() << " _ " << x.second.Buyer() << " _ " << x.second.Amount() << endl;
            }
        }

//        cout << " ---- " << endl;

        for (auto x : companies.at(companyName).accepted) {
            if (companies.at(companyName).invoices.count(x.first) == 0) {
                sortedInvoicesList.push_back(x.second);
//                cout << "__ " << x.second.Seller() << " _ " << x.second.Buyer() << " _ " << x.second.Amount() << endl;
            }
        }

//        cout << " ---- " << endl;

        sortedInvoicesList.sort(CompareInvoice(sortBy));

        return sortedInvoicesList;
    }

private:
    unordered_map<string, CCompany> companies;
};

#ifndef __PROGTEST__

bool equalLists (const list<CInvoice>& a, const list<CInvoice>& b) {

    for (auto x: a) {
        cout << x.Seller() << " _ " << x.Buyer() << " _ " << x.Amount() << " _ " << x.Date().Day() << ". " << x.Date().Month() << ". " << x.Date().Year() << endl;
    }

    cout << endl << " *********** " << endl << endl;

    for (auto x: b) {
        cout << x.Seller() << " _ " << x.Buyer() << " _ " << x.Amount() << " _ " << x.Date().Day() << ". " << x.Date().Month() << ". " << x.Date().Year() << endl;
    }

    if (a.size() != b.size()) {
        return false;
    }

    if (!a.empty()) {
        for (unsigned int i = 0; i < a.size(); ++i) {
            CInvoice ai = a.front();
            CInvoice bi = b.front();

            if (ai.Buyer() != bi.Buyer() ||
                ai.Seller() != bi.Seller() ||
                !ai.Date().Compare(bi.Date()) ||
                ai.Amount() != bi.Amount() ||
                ai.VAT() != bi.VAT()) {
                return false;
            }
        }
    }

    return true;
}

int main (void) {
    CVATRegister r;

    CDate t1(2017, 2, 5);
    CDate t2(2017, 2, 6);
    CDate t3(2017, 2, 3);

    cout << t1.Compare(t1) << endl;
    cout << t1.Compare(t2) << endl;
    cout << t1.Compare(t3) << endl;

    assert (r.RegisterCompany("first Company"));
    assert (r.RegisterCompany("Second     Company"));
    assert (r.RegisterCompany("ThirdCompany, Ltd."));
    assert (r.RegisterCompany("Third Company, Ltd."));
    assert (!r.RegisterCompany("Third Company, Ltd."));
    assert (!r.RegisterCompany(" Third  Company,  Ltd.  "));

    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));

    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, false).AddKey(CSortOpt::BY_DATE, false)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)
                           }));

    assert (r.AddAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
    assert (r.AddAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (!r.AddAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.AddAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));

    /*
    assert (r.RegisterCompany("first Company"));
    assert (r.RegisterCompany("Second     Company"));
    assert (r.RegisterCompany("ThirdCompany, Ltd."));
    assert (r.RegisterCompany("Third Company, Ltd."));
    assert (!r.RegisterCompany("Third Company, Ltd."));
    assert (!r.RegisterCompany(" Third  Company,  Ltd.  "));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
    assert (r.AddIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
    assert (!r.AddIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));
    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, false).AddKey(CSortOpt::BY_DATE, false)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)
                           }));
    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_DATE, true).AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, true)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000)
                           }));
    assert (equalLists(r.Unmatched("First Company",
                                   CSortOpt().AddKey(CSortOpt::BY_VAT, true).AddKey(CSortOpt::BY_AMOUNT, true).AddKey(CSortOpt::BY_DATE, true).AddKey(CSortOpt::BY_SELLER,
                                                                                                                                                      true).AddKey(
                                       CSortOpt::BY_BUYER, true)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)
                           }));
    assert (equalLists(r.Unmatched("First Company", CSortOpt()),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)
                           }));
    assert (equalLists(r.Unmatched("second company", CSortOpt().AddKey(CSortOpt::BY_DATE, false)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400, 34.000000)
                           }));
    assert (equalLists(r.Unmatched("last company", CSortOpt().AddKey(CSortOpt::BY_VAT, true)),
                       list<CInvoice>
                           {
                           }));
    assert (r.AddAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
    assert (r.AddAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.AddAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, true).AddKey(CSortOpt::BY_DATE, true)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)
                           }));
    assert (!r.DelIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
    assert (!r.DelIssued(CInvoice(CDate(2000, 1, 1), "A First Company", "Second Company ", 200, 30)));
    assert (!r.DelIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Hand", 200, 30)));
    assert (!r.DelIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 1200, 30)));
    assert (!r.DelIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 200, 130)));
    assert (r.DelIssued(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company", 200, 30)));
    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, true).AddKey(CSortOpt::BY_DATE, true)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)
                           }));
    assert (r.DelAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, true).AddKey(CSortOpt::BY_DATE, true)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)
                           }));
    assert (r.DelIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (equalLists(r.Unmatched("First Company", CSortOpt().AddKey(CSortOpt::BY_SELLER, true).AddKey(CSortOpt::BY_BUYER, true).AddKey(CSortOpt::BY_DATE, true)),
                       list<CInvoice>
                           {
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                               CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)
                           }));
   */
    return 0;
}

#endif /* __PROGTEST__ */
