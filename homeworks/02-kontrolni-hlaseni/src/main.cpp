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
    bool NewCompany (const std::string &name, const std::string &addr, const std::string &taxID);
    bool CancelCompany (const std::string &name, const std::string &addr);
    bool CancelCompany (const std::string &taxID);
    bool Invoice (const std::string &taxID, unsigned int amount);
    bool Invoice (const std::string &name, const std::string &addr, unsigned int amount);
    bool Audit (const std::string &name, const std::string &addr, unsigned int &sumIncome) const;
    bool Audit (const std::string &taxID, unsigned int &sumIncome) const;
    unsigned int MedianInvoice (void) const;
private:
    class Company {
    public:
        std::size_t nameAddress;
        std::size_t id;
        unsigned int income;
    };

    std::vector<Company *> companyNameList;
    std::vector<Company *> companyIdList;
    std::vector<unsigned int> companyInvoiceList;
    static bool compareNameList (const Company *company1, const Company *company2);
    static bool compareIdList (const Company *company1, const Company *company2);
};

CVATRegister::CVATRegister (void) {

}

CVATRegister::~CVATRegister (void) {
    // only once, because companyIdList has the same pointers
    for (unsigned int i = 0; i < companyNameList.size(); i++) {
        if (companyNameList[i] != NULL) {
            delete companyNameList[i];
        }
    }
}

bool CVATRegister::NewCompany (const std::string &name, const std::string &addr, const std::string &taxID) {
    Company *company = new Company;

    company->income = 0;

    // temporary data
    std::string companyName = name;
    std::string companyAddress = addr;

    // transform and hash name + adress
    std::transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.end(), companyAddress.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.begin() + 1, companyAddress.begin(), ::toupper);
    company->nameAddress = std::hash<std::string>{}(companyName + companyAddress);

    // transform and hash id
    company->id = std::hash<std::string>{}(taxID);

    // if company matches something in nameList or idList, return false
    if (std::binary_search(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList) ||
        std::binary_search(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList)) {
        delete company;
        return false;
    }

    // add company
    companyNameList.insert(std::lower_bound(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList), company);
    companyIdList.insert(std::lower_bound(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList), company);
    return true;
}

bool CVATRegister::CancelCompany (const std::string &name, const std::string &addr) {
    Company *company = new Company;

    // temporary data
    std::string companyName = name;
    std::string companyAddress = addr;

    // transform and hash name + adress
    std::transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.end(), companyAddress.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.begin() + 1, companyAddress.begin(), ::toupper);
    company->nameAddress = std::hash<std::string>{}(companyName + companyAddress);

    // find iterator
    std::vector<CVATRegister::Company *>::iterator iterator = std::lower_bound(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList);

    // if company is found then remove company from both lists
    if (iterator >= companyNameList.end()  || (*iterator)->nameAddress != company->nameAddress) {
        delete company;
        return false;
    }

    company->id = (*iterator)->id;

    companyNameList.erase(std::lower_bound(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList));
    companyIdList.erase(std::lower_bound(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList));

    delete company;
    return true;
}

bool CVATRegister::CancelCompany (const std::string &taxID) {
    Company *company = new Company;

    // transform and hash id
    company->id = std::hash<std::string>{}(taxID);

    // find iterator
    std::vector<CVATRegister::Company *>::iterator iterator = std::lower_bound(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList);

    // if company is found then remove company from both lists
    if (iterator >= companyIdList.end() || (*iterator)->id != company->id) {
        delete company;
        return false;
    }

    company->nameAddress = (*iterator)->nameAddress;

    companyIdList.erase(std::lower_bound(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList));
    companyNameList.erase(std::lower_bound(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList));
    delete company;
    return true;
}

bool CVATRegister::Invoice (const std::string &taxID, unsigned int amount) {
    Company *company = new Company;

    // transform and hash id
    company->id = std::hash<std::string>{}(taxID);

    // find iterator
    std::vector<CVATRegister::Company *>::iterator iterator = std::lower_bound(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList);

    // if company is found then remove company from both lists
    if (iterator >= companyIdList.end() || (*iterator)->id != company->id) {
        delete company;
        return false;
    }

    companyInvoiceList.push_back(amount);
    (*iterator)->income += amount;

    delete company;
    return true;
}

bool CVATRegister::Invoice (const std::string &name, const std::string &addr, unsigned int amount) {
    Company *company = new Company;

    // temporary data
    std::string companyName = name;
    std::string companyAddress = addr;

    // transform and hash name + adress
    std::transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.end(), companyAddress.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.begin() + 1, companyAddress.begin(), ::toupper);
    company->nameAddress = std::hash<std::string>{}(companyName + companyAddress);

    // find iterator
    std::vector<CVATRegister::Company *>::iterator iterator = std::lower_bound(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList);

    // if company is found then remove company from both lists
    if (iterator >= companyNameList.end() || (*iterator)->nameAddress != company->nameAddress) {
        delete company;
        return false;
    }

    companyInvoiceList.push_back(amount);
    (*iterator)->income += amount;

    delete company;
    return true;
}

bool CVATRegister::Audit (const std::string &name, const std::string &addr, unsigned int &sumIncome) const {
    Company *company = new Company;

    // temporary data
    std::string companyName = name;
    std::string companyAddress = addr;

    // transform and hash name + adress
    std::transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.end(), companyAddress.begin(), ::tolower);
    std::transform(companyAddress.begin(), companyAddress.begin() + 1, companyAddress.begin(), ::toupper);
    company->nameAddress = std::hash<std::string>{}(companyName + companyAddress);

    // find iterator
    std::vector<CVATRegister::Company *>::const_iterator iterator = std::lower_bound(companyNameList.begin(), companyNameList.end(), company, CVATRegister::compareNameList);

    // if company is found then remove company from both lists
    if (iterator >= companyNameList.end() || (*iterator)->nameAddress != company->nameAddress) {
        delete company;
        return false;
    }

    sumIncome = (*iterator)->income;
    delete company;
    return true;
}

bool CVATRegister::Audit (const std::string &taxID, unsigned int &sumIncome) const {
    Company *company = new Company;

    // transform and hash id
    company->id = std::hash<std::string>{}(taxID);

    // find iterator
    std::vector<CVATRegister::Company *>::const_iterator iterator = std::lower_bound(companyIdList.begin(), companyIdList.end(), company, CVATRegister::compareIdList);

    // if company is found then remove company from both lists
    if (iterator >= companyIdList.end() || (*iterator)->id != company->id) {
        delete company;
        return false;
    }

    sumIncome = (*iterator)->income;
    delete company;
    return true;
}

unsigned int CVATRegister::MedianInvoice (void) const {
    if (companyInvoiceList.size() == 0) {
        return 0;
    }

    std::vector<unsigned int> companyInvoiceListSorted;
    companyInvoiceListSorted = companyInvoiceList;

    std::sort(companyInvoiceListSorted.begin(), companyInvoiceListSorted.end());

    return companyInvoiceListSorted[(companyInvoiceListSorted.size() / 2)];
}

bool CVATRegister::compareNameList (const CVATRegister::Company *company1, const CVATRegister::Company *company2) {
    if (company1 != NULL && company2 != NULL) {
        return company1->nameAddress < company2->nameAddress;
    }

    return false;
}

bool CVATRegister::compareIdList (const CVATRegister::Company *company1, const CVATRegister::Company *company2) {
    if (company1 != NULL && company2 != NULL) {
        return company1->id < company2->id;
    }

    return false;
}

#ifndef __PROGTEST__

int main (void) {
    unsigned int sumIncome;

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
