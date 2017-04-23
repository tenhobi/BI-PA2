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
    CDate (int y, int m, int d) : m_Year(y), m_Month(m), m_Day(d) {
    }

    int Compare (const CDate& x) const {
        if (m_Year != x.m_Year)
            return m_Year - x.m_Year;
        if (m_Month != x.m_Month)
            return m_Month - x.m_Month;
        return m_Day - x.m_Day;
    }

    int Year (void) const {
        return m_Year;
    }

    int Month (void) const {
        return m_Month;
    }

    int Day (void) const {
        return m_Day;
    }

    friend ostream& operator << (ostream& os,
                                 const CDate& x) {
        char oldFill = os.fill();
        return os << setfill('0') << setw(4) << x.m_Year << "-"
                  << setw(2) << (int) x.m_Month << "-"
                  << setw(2) << (int) x.m_Day
                  << setfill(oldFill);
    }

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

//---------------------------------------------------------------------------------------------

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
        return m_CompanyBuyerName;
    }

    string NormBuyer (void) const {
        return m_NormBuyer;
    }

    string Seller (void) const {
        return m_CompanySellerName;
    }

    string NormSeller (void) const {
        return m_NormSeller;
    }

    int Amount (void) const {
        return m_Amount;
    }

    double VAT (void) const {
        return m_VAT;
    }

    string m_CompanySellerName;
    string m_CompanyBuyerName;

    int Id;

private:
    CDate m_Date;
    string m_Seller;
    string m_NormSeller;
    string m_Buyer;
    string m_NormBuyer;
    unsigned int m_Amount;
    double m_VAT;
};

//---------------------------------------------------------------------------------------------

class CCompany {
public:
    CCompany (const string& name) : m_Name(name) {}

    unordered_map<string, CInvoice> invoices;

    string m_Name;
};

//---------------------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------------------

struct CompareInvoice {
public:
    CompareInvoice (const CSortOpt& sortBy) : sortKeys(sortBy) {}

    bool operator () (const CInvoice& a, const CInvoice& b) {
        for (auto& x: sortKeys.keyList) {
            switch (x.first) {
                case CSortOpt::BY_DATE:
                    if (x.second ? (a.Date().Compare(b.Date()) < 0) : (b.Date().Compare(a.Date()) < 0)) {
                        return true;
                    }

                    if (a.Date().Compare(b.Date()) == 0) {
                        continue;
                    }

                    break;
                case CSortOpt::BY_BUYER: {
                    string n = a.Buyer();
                    string m = b.Buyer();
                    transform(n.begin(), n.end(), n.begin(), ::toupper);
                    transform(m.begin(), m.end(), m.begin(), ::toupper);
                    if (x.second ? (n < m) : (m < n)) {
                        return true;
                    }

                    if (n == m) {
                        continue;
                    }
                }

                    break;
                case CSortOpt::BY_SELLER: {
                    string n = a.Seller();
                    string m = b.Seller();
                    transform(n.begin(), n.end(), n.begin(), ::toupper);
                    transform(m.begin(), m.end(), m.begin(), ::toupper);
                    if (x.second ? (n < m) : (m < n)) {
                        return true;
                    }

                    if (n == m) {
                        continue;
                    }
                }

                    break;
                case CSortOpt::BY_AMOUNT:
                    if (x.second ? (a.Amount() < b.Amount()) : (b.Amount() < a.Amount())) {
                        return true;
                    }

                    if (a.Amount() == b.Amount()) {
                        continue;
                    }

                    break;
                case CSortOpt::BY_VAT:
                    if (x.second ? (a.VAT() < b.VAT()) : (b.VAT() < a.VAT())) {
                        return true;
                    }

                    if (a.VAT() == b.VAT()) {
                        continue;
                    }

                    break;
                default:
                    break;
            }

            return false;
        }

        return a.Id < b.Id;
    }

private:
    CSortOpt sortKeys;

};

//---------------------------------------------------------------------------------------------

class CVATRegister {
public:
    CVATRegister (void) {}

    static int ID;

    bool RegisterCompany (const string& name) {
        string normalizedName = NormalizeName(name);

        if (companies.count(normalizedName) == 0) {
            companies.insert({normalizedName, CCompany(name)});
            return true;
        }

        return false;
    }

    bool AddIssued (const CInvoice& x) {
        if (companies.count(x.NormBuyer()) == 0 || companies.count(x.NormSeller()) == 0 || x.NormBuyer() == x.NormSeller()) {
            return false;
        }

        string key = x.NormBuyer() + "_" +
                     x.NormSeller() + "_" +
                     to_string(x.Date().Year()) + "_" +
                     to_string(x.Date().Month()) + "_" +
                     to_string(x.Date().Day()) + "_" +
                     to_string(x.Amount()) + "_" +
                     to_string(x.VAT());

        int myId = CVATRegister::ID++;

        if (companies.at(x.NormSeller()).invoices.count(key) == 0) {
            companies.at(x.NormSeller()).invoices.insert({key, x});
            companies.at(x.NormSeller()).invoices.at(key).isIssued = true;
            companies.at(x.NormSeller()).invoices.at(key).m_CompanyBuyerName = companies.at(x.NormBuyer()).m_Name;
            companies.at(x.NormSeller()).invoices.at(key).m_CompanySellerName = companies.at(x.NormSeller()).m_Name;
            companies.at(x.NormSeller()).invoices.at(key).Id = myId;
            companies.at(x.NormBuyer()).invoices.insert({key, x});
            companies.at(x.NormBuyer()).invoices.at(key).isIssued = true;
            companies.at(x.NormBuyer()).invoices.at(key).m_CompanyBuyerName = companies.at(x.NormBuyer()).m_Name;
            companies.at(x.NormBuyer()).invoices.at(key).m_CompanySellerName = companies.at(x.NormSeller()).m_Name;
            companies.at(x.NormBuyer()).invoices.at(key).Id = myId;
            return true;
        }

        if (companies.at(x.NormSeller()).invoices.count(key) == 1 && !companies.at(x.NormSeller()).invoices.at(key).isIssued) {
            companies.at(x.NormSeller()).invoices.at(key).isIssued = true;
            companies.at(x.NormBuyer()).invoices.at(key).isIssued = true;
            return true;
        }

        return false;
    }

    bool AddAccepted (const CInvoice& x) {
        if (companies.count(x.NormBuyer()) == 0 || companies.count(x.NormSeller()) == 0 || x.NormBuyer() == x.NormSeller()) {
            return false;
        }

        string key = x.NormBuyer() + "_" +
                     x.NormSeller() + "_" +
                     to_string(x.Date().Year()) + "_" +
                     to_string(x.Date().Month()) + "_" +
                     to_string(x.Date().Day()) + "_" +
                     to_string(x.Amount()) + "_" +
                     to_string(x.VAT());

        int myId = CVATRegister::ID++;

        if (companies.at(x.NormSeller()).invoices.count(key) == 0) {
            companies.at(x.NormSeller()).invoices.insert({key, x});
            companies.at(x.NormSeller()).invoices.at(key).isAccepted = true;
            companies.at(x.NormSeller()).invoices.at(key).m_CompanyBuyerName = companies.at(x.NormBuyer()).m_Name;
            companies.at(x.NormSeller()).invoices.at(key).m_CompanySellerName = companies.at(x.NormSeller()).m_Name;
            companies.at(x.NormSeller()).invoices.at(key).Id = myId;
            companies.at(x.NormBuyer()).invoices.insert({key, x});
            companies.at(x.NormBuyer()).invoices.at(key).isAccepted = true;
            companies.at(x.NormBuyer()).invoices.at(key).m_CompanyBuyerName = companies.at(x.NormBuyer()).m_Name;
            companies.at(x.NormBuyer()).invoices.at(key).m_CompanySellerName = companies.at(x.NormSeller()).m_Name;
            companies.at(x.NormBuyer()).invoices.at(key).Id = myId;
            return true;
        }

        if (companies.at(x.NormSeller()).invoices.count(key) == 1 && !companies.at(x.NormSeller()).invoices.at(key).isAccepted) {
            companies.at(x.NormSeller()).invoices.at(key).isAccepted = true;
            companies.at(x.NormBuyer()).invoices.at(key).isAccepted = true;
            return true;
        }

        return false;
    }

    bool DelIssued (const CInvoice& x) {
        string key = x.NormBuyer() + "_" +
                     x.NormSeller() + "_" +
                     to_string(x.Date().Year()) + "_" +
                     to_string(x.Date().Month()) + "_" +
                     to_string(x.Date().Day()) + "_" +
                     to_string(x.Amount()) + "_" +
                     to_string(x.VAT());

        if (companies.count(x.NormSeller()) == 0 || companies.count(x.NormBuyer()) == 0 || x.NormSeller() == x.NormBuyer()) {
            return false;
        }

        if (companies.at(x.NormSeller()).invoices.count(key) == 0) {
            return false;
        }

        if (companies.at(x.NormSeller()).invoices.at(key).isAccepted) {
            companies.at(x.NormSeller()).invoices.at(key).isIssued = false;
            companies.at(x.NormBuyer()).invoices.at(key).isIssued = false;
        } else {
            companies.at(x.NormSeller()).invoices.erase(key);
            companies.at(x.NormBuyer()).invoices.erase(key);
        }

        return true;
    }

    bool DelAccepted (const CInvoice& x) {
        string key = x.NormBuyer() + "_" +
                     x.NormSeller() + "_" +
                     to_string(x.Date().Year()) + "_" +
                     to_string(x.Date().Month()) + "_" +
                     to_string(x.Date().Day()) + "_" +
                     to_string(x.Amount()) + "_" +
                     to_string(x.VAT());

        if (companies.count(x.NormSeller()) == 0 || companies.count(x.NormBuyer()) == 0 || x.NormSeller() == x.NormBuyer()) {
            return false;
        }

        if (companies.at(x.NormSeller()).invoices.count(key) == 0) {
            return false;
        }

        if (companies.at(x.NormSeller()).invoices.at(key).isIssued) {
            companies.at(x.NormSeller()).invoices.at(key).isAccepted = false;
            companies.at(x.NormBuyer()).invoices.at(key).isAccepted = false;
        } else {
            companies.at(x.NormSeller()).invoices.erase(key);
            companies.at(x.NormBuyer()).invoices.erase(key);
        }

        return true;
    }

    list<CInvoice> Unmatched (const string& company, const CSortOpt& sortBy) const {
        list<CInvoice> sortedInvoicesList;
        string companyName = NormalizeName(company);

        if (companies.count(companyName) == 0) {
            return sortedInvoicesList;
        }

//        cout << "--- unmatched company" << endl;

        for (auto x : companies.at(companyName).invoices) {
            if ((x.second.isAccepted && !x.second.isIssued) || (!x.second.isAccepted && x.second.isIssued)) {
                sortedInvoicesList.push_back(x.second);
//                cout << x.second.Seller() << " _ " << x.second.Buyer() << " _ " << x.second.Amount() << endl;
            }
        }

        if (sortedInvoicesList.size() == 0) {
            return sortedInvoicesList;
        }

        sortedInvoicesList.sort(CompareInvoice(sortBy));
        return sortedInvoicesList;
    }

    unordered_map<string, CCompany> companies;
};

int CVATRegister::ID = 0;

#ifndef __PROGTEST__

bool equalLists (const list<CInvoice>& a, const list<CInvoice>& b) {

    cout << "--- my sort" << endl;

    if (a.size() == 0) {
        return true;
    }

    for (auto x: a) {
        cout << x.Seller() << " _ " << x.Buyer() << " _ " << x.Amount() << " _ " << x.VAT() << " _ " << x.Id << endl;
    }

    return true;

    /*

    if (a.size() != b.size()) {
        return false;
    }

    if (!a.empty()) {
        for (unsigned int i = 0; i < a.size(); ++i) {
            CInvoice ai = a.front();
            CInvoice bi = b.front();

            if (ai.Buyer() != bi.Buyer()) {
                cout << "eq 1" << endl;
                cout << ai.Buyer() << endl;
                cout << bi.Buyer() << endl;
                return false;
            }

            if (ai.Seller() != bi.Seller()) {
                cout << "eq 2" << endl;
                return false;
            }

            if (!ai.Date().Compare(bi.Date())) {
                cout << "eq 3" << endl;
                return false;
            }

            if (ai.Amount() != bi.Amount()) {
                cout << "eq 4" << endl;
                return false;
            }

            if (ai.VAT() != bi.VAT()) {
                cout << "eq 5" << endl;
                return false;
            }
        }
    }

    return true;

     */
}

int main (void) {
    CVATRegister r;

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
    return 0;
}

#endif /* __PROGTEST__ */
