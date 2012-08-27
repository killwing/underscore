#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "underscore.h"
using namespace std;

int main() {
    int a1[] {8, 6, 4, 1, 3, 9, 7, 5, 2};
    _::each(a1, [](int i) {
        cout << i << endl;
    });

    vector<int> v1 {2, 5, 7, 9, 3, 1, 4, 6, 8};
    _::each(v1, [](int i) {
        cout << i << endl;
    });

    map<int, string> m1 {{1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}};
    _::each(m1, [](string s, int i) {
        cout << i << s << endl;
    });

    map<int, string> m2 {{1, "x"}, {2, "x"}, {3, "x"}, {4, "x"}};
    _::each(m2, [](string s, int i) {
        cout << i << s << endl;
    });

    assert(!_::all(v1, [](int i) { return i > 5; }));
    assert(_::all(v1, [](int i) { return i > 0; }));

    assert(!_::all(m1, [](string s, int i) { return s == "a"; }));
    assert(_::all(m2, [](string s, int i) { return s == "x"; }));

    assert(!_::any(v1, [](int i) { return i > 9; }));
    assert(_::any(v1, [](int i) { return i > 8; }));

    assert(!_::any(m1, [](string s, int i) { return s == "x"; }));
    assert(_::any(m1, [](string s, int i) { return s == "d"; }));

    cout << "All tests passed." << endl;
    return 0;
}
