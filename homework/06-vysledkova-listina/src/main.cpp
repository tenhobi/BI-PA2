#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>

using namespace std;
#endif /* __PROGTEST__ */

class OrderingDoesNotExistException {
};

class DuplicateMatchException {
};

template<typename _M>
class CContest {
public:
    CContest () {

    }

    ~CContest () {

    }

    CContest& AddMatch (const string& contestant1, const string& contestant2, const _M& result) {
        if (recordMap.count(pair(contestant1, contestant2)) != 0) {
            throw DuplicateMatchException();
        }

        recordMap.insert(pair(pair(contestant1, contestant2), result));
        return *this;
    }
//
//    bool IsOrdered (function<int (_M)> comparator) {
//        return false;
//    }

    template<class fn>
    bool IsOrdered (const fn& komparator) {
        recordList.sort(komparator);
        return false;
    }

    list<string> Results (function<int (_M)> comparator) {
        list<string> result;
        return result;
    }

    class Record {
    public:
        string first;
        string second;
        _M result;
    };

    map<pair<string, string>, _M> recordMap;
};

#ifndef __PROGTEST__

struct CMatch {
public:
    CMatch (int a,
            int b)
        : m_A(a),
          m_B(b) {
    }

    int m_A;
    int m_B;
};

class HigherScoreThreshold {
public:
    HigherScoreThreshold (int diffAtLeast)
        : m_DiffAtLeast(diffAtLeast) {
    }

    int operator () (const CMatch& x) const {
        return (x.m_A > x.m_B + m_DiffAtLeast) - (x.m_B > x.m_A + m_DiffAtLeast);
    }

private:
    int m_DiffAtLeast;
};

int HigherScore (const CMatch& x) {
    return (x.m_A > x.m_B) - (x.m_B > x.m_A);
}

int main (void) {
    CContest<CMatch> x;

    x.AddMatch("C++", "Pascal", CMatch(10, 3))
        .AddMatch("C++", "Java", CMatch(8, 1))
        .AddMatch("Pascal", "Basic", CMatch(40, 0))
        .AddMatch("Java", "PHP", CMatch(6, 2))
        .AddMatch("Java", "Pascal", CMatch(7, 3))
        .AddMatch("PHP", "Basic", CMatch(10, 0));

    assert (!x.IsOrdered(HigherScore));
    try {
        list<string> res = x.Results(HigherScore);
        assert ("Exception missing!" == NULL);
    }
    catch (const OrderingDoesNotExistException& e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    x.AddMatch("PHP", "Pascal", CMatch(3, 6));

    assert (x.IsOrdered(HigherScore));
    try {
        list<string> res = x.Results(HigherScore);
        assert ((res == list<string>{"C++", "Java", "Pascal", "PHP", "Basic"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == NULL);
    }

    /*

    assert (!x.IsOrdered(HigherScoreThreshold(3)));
    try {
        list<string> res = x.Results(HigherScoreThreshold(3));
        assert ("Exception missing!" == NULL);
    }
    catch (const OrderingDoesNotExistException& e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    assert (x.IsOrdered([] (const CMatch& x) {
        return (x.m_A < x.m_B) - (x.m_B < x.m_A);
    }));
    try {
        list<string> res = x.Results([] (const CMatch& x) {
            return (x.m_A < x.m_B) - (x.m_B < x.m_A);
        });
        assert ((res == list<string>{"Basic", "PHP", "Pascal", "Java", "C++"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == NULL);
    }

    CContest<bool> y;

    y.AddMatch("Python", "PHP", true)
        .AddMatch("PHP", "Perl", true)
        .AddMatch("Perl", "Bash", true)
        .AddMatch("Bash", "JavaScript", true)
        .AddMatch("JavaScript", "VBScript", true);

    assert (y.IsOrdered([] (bool v) {
        return v ? 10 : -10;
    }));
    try {
        list<string> res = y.Results([] (bool v) {
            return v ? 10 : -10;
        });
        assert ((res == list<string>{"Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == NULL);
    }

    y.AddMatch("PHP", "JavaScript", false);
    assert (!y.IsOrdered([] (bool v) {
        return v ? 10 : -10;
    }));
    try {
        list<string> res = y.Results([] (bool v) {
            return v ? 10 : -10;
        });
        assert ("Exception missing!" == NULL);
    }
    catch (const OrderingDoesNotExistException& e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    try {
        y.AddMatch("PHP", "JavaScript", false);
        assert ("Exception missing!" == NULL);
    }
    catch (const DuplicateMatchException& e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }

    try {
        y.AddMatch("JavaScript", "PHP", true);
        assert ("Exception missing!" == NULL);
    }
    catch (const DuplicateMatchException& e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == NULL);
    }
     */
    return 0;
}

#endif /* __PROGTEST__ */
