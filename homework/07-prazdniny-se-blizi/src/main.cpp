#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;
#endif /* __PROGTEST_ */

class CThing {
public:
    int grams;
    bool dangerous = false;

    CThing (int grams, bool dangerous) : grams(grams), dangerous(dangerous) {}

    CThing () {}

    virtual ~CThing () {}

    virtual ostream& Print (ostream& os) const {
        return os;
    }

    friend ostream& operator << (ostream& os, const CThing& thing) {
        return thing.Print(os);
    }

    virtual shared_ptr<CThing> Clone () const {
        return shared_ptr<CThing>( new CThing(*this));
    }
};

class CKnife : public CThing {
public:
    int bladeLength;

    CKnife (int bladeLength) : CThing(100, bladeLength > 7), bladeLength(bladeLength) {}

    virtual ~CKnife () {}

    ostream& Print (ostream& os) const override {
        os << "Knife, blade: " << bladeLength << " cm" << endl;
        return CThing::Print(os);
    }

    virtual shared_ptr<CThing> Clone () const {
        return shared_ptr<CThing>( new CKnife(*this));
    }
};

class CHolder {
public:
    int grams;

    CHolder (int grams) : grams(grams) {}

    CHolder& Add (const CThing& thing) {
        things.push_back(thing.Clone());
        return *this;
    }

    virtual ~CHolder () {}

    int Weight () const {
        int result = grams;

        for (auto& thing: things) {
            result += thing->grams;
        }

        return result;
    }

    int Count () const {
        return (int) things.size();
    }

    bool Danger () const {
        for (const auto& thing: things) {
            if (thing->dangerous) {
                return true;
            }
        }

        return false;
    }

    bool IdenticalContents (const CHolder& holder) const {
        int gramsSum[4] = {100, 150, 750, 500};

        for (unsigned int i = 0; i < 4; ++i) {
            int first = 0;
            int second = 0;

            for (auto& thing: things) {
                if (thing->grams == gramsSum[i]) {
                    ++first;
                }
            }

            for (auto& thing: holder.things) {
                if (thing->grams == gramsSum[i]) {
                    ++second;
                }
            }

            if (second != first) {
                return false;
            }
        }

        return true;
    }

    virtual ostream& Print (ostream& os) const {
        for (unsigned int i = 0; i < things.size(); i++) {
            os << (i == things.size() - 1 ? "\\" : "+") << "-" << *things[i];
        }

        return os;
    }

    friend ostream& operator << (ostream& os, const CHolder& holder) {
        return holder.Print(os);
    }

private:
    vector<shared_ptr<CThing>> things;
};

class CClothes : public CThing {
public:
    string description;

    CClothes (string description) : CThing(500, false), description(description) {}

    virtual ~CClothes () {}

    ostream& Print (ostream& os) const override {
        os << "Clothes (" << description << ")" << endl;
        return CThing::Print(os);
    }

    virtual shared_ptr<CThing> Clone () const {
        return shared_ptr<CThing>( new CClothes(*this));
    }
};

class CShoes : public CThing {
public:
    CShoes () : CThing(750, false) {}

    virtual ~CShoes () {}

    ostream& Print (ostream& os) const override {
        os << "Shoes" << endl;
        return CThing::Print(os);
    }

    virtual shared_ptr<CThing> Clone () const {
        return shared_ptr<CThing>( new CShoes(*this));
    }
};

class CMobile : public CThing {
public:
    string manufacturer;
    string model;

    CMobile (string manufacturer, string model) : CThing(150, manufacturer == "Samsung" && model == "Galaxy Note S7"), manufacturer(manufacturer), model(model) {}

    virtual ~CMobile () {}

    ostream& Print (ostream& os) const override {
        os << "Mobile " << model << " by: " << manufacturer << endl;
        return CThing::Print(os);
    }

    virtual shared_ptr<CThing> Clone () const {
        return shared_ptr<CThing>( new CMobile(*this));
    }
};

class CSuitcase : public CHolder {
public:
    int width;
    int height;
    int depth;

    CSuitcase (int width, int height, int depth) : CHolder(2000), width(width), height(height), depth(depth) {}

    virtual ~CSuitcase () {}

    ostream& Print (ostream& os) const override {
        os << "Suitcase " << width << "x" << height << "x" << depth << endl;
        return CHolder::Print(os);
    }
};

class CBackpack : public CHolder {
public:
    CBackpack () : CHolder(1000) {}

    virtual ~CBackpack () {}

    ostream& Print (ostream& os) const override {
        os << "Backpack" << endl;
        return CHolder::Print(os);
    }
};

#ifndef __PROGTEST__

int main (void) {
    CSuitcase x(1, 2, 3);
    CBackpack y;
    ostringstream os;
    x.Add(CKnife(7));
    x.Add(CClothes("red T-shirt"));
    x.Add(CClothes("black hat"));
    x.Add(CShoes());
    x.Add(CClothes("green pants"));
    x.Add(CClothes("blue jeans"));
    x.Add(CMobile("Samsung", "J3"));
    x.Add(CMobile("Tamtung", "Galaxy Note S7"));
    os.str("");
    os << x;
    assert (os.str() == "Suitcase 1x2x3\n"
        "+-Knife, blade: 7 cm\n"
        "+-Clothes (red T-shirt)\n"
        "+-Clothes (black hat)\n"
        "+-Shoes\n"
        "+-Clothes (green pants)\n"
        "+-Clothes (blue jeans)\n"
        "+-Mobile J3 by: Samsung\n"
        "\\-Mobile Galaxy Note S7 by: Tamtung\n");
    assert (x.Count() == 8);
    assert (x.Weight() == 5150);
    assert (!x.Danger());
    x.Add(CKnife(8));
    os.str("");
    os << x;
    assert (os.str() == "Suitcase 1x2x3\n"
        "+-Knife, blade: 7 cm\n"
        "+-Clothes (red T-shirt)\n"
        "+-Clothes (black hat)\n"
        "+-Shoes\n"
        "+-Clothes (green pants)\n"
        "+-Clothes (blue jeans)\n"
        "+-Mobile J3 by: Samsung\n"
        "+-Mobile Galaxy Note S7 by: Tamtung\n"
        "\\-Knife, blade: 8 cm\n");
    assert (x.Count() == 9);
    assert (x.Weight() == 5250);
    assert (x.Danger());
    y.Add(CKnife(7))
        .Add(CClothes("red T-shirt"))
        .Add(CShoes());
    y.Add(CMobile("Samsung", "Galaxy Note S7"));
    y.Add(CShoes());
    y.Add(CClothes("blue jeans"));
    y.Add(CClothes("black hat"));
    y.Add(CClothes("green pants"));
    os.str("");
    os << y;
    assert (os.str() == "Backpack\n"
        "+-Knife, blade: 7 cm\n"
        "+-Clothes (red T-shirt)\n"
        "+-Shoes\n"
        "+-Mobile Galaxy Note S7 by: Samsung\n"
        "+-Shoes\n"
        "+-Clothes (blue jeans)\n"
        "+-Clothes (black hat)\n"
        "\\-Clothes (green pants)\n");
    assert (y.Count() == 8);
    assert (y.Weight() == 4750);
    assert (y.Danger());
    y.Add(CMobile("Samsung", "J3"));
    y.Add(CMobile("Tamtung", "Galaxy Note S7"));
    y.Add(CKnife(8));
    os.str("");
    os << y;
    assert (os.str() == "Backpack\n"
        "+-Knife, blade: 7 cm\n"
        "+-Clothes (red T-shirt)\n"
        "+-Shoes\n"
        "+-Mobile Galaxy Note S7 by: Samsung\n"
        "+-Shoes\n"
        "+-Clothes (blue jeans)\n"
        "+-Clothes (black hat)\n"
        "+-Clothes (green pants)\n"
        "+-Mobile J3 by: Samsung\n"
        "+-Mobile Galaxy Note S7 by: Tamtung\n"
        "\\-Knife, blade: 8 cm\n");
    assert (y.Count() == 11);
    assert (y.Weight() == 5150);
    assert (y.Danger());
    assert (!x.IdenticalContents(y));
    assert (!y.IdenticalContents(x));
    x.Add(CMobile("Samsung", "Galaxy Note S7"));
    assert (!x.IdenticalContents(y));
    assert (!y.IdenticalContents(x));
    x.Add(CShoes());
    assert (x.IdenticalContents(y));
    assert (y.IdenticalContents(x));
    assert (y.IdenticalContents(y));
    assert (x.IdenticalContents(x));
    return 0;
}

#endif /* __PROGTEST__ */
