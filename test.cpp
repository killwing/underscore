#include <iostream>
#include <cassert>

#include <array>
#include <initializer_list>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set> // multiset
#include <unordered_set> // unordered_multiset
#include <map> // multimap
#include <unordered_map> // unordered_multimap

#include "underscore.h"
using namespace std;


template<typename T> void
testNonMappedContainer(const string& name) {
    // assume value could be number
    T container { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // each
    int sum = 0;
    _::each(container, [&](typename T::value_type v) {
        sum += v;
    });
    assert(sum == 45); // just check sum

    // all
    assert(_::all(container, [](typename T::value_type v) {
        return v >= 0;
    }));

    // any
    assert(_::any(container, [](typename T::value_type v) {
        return v > 8;
    }));

    // filter
    auto filtered = _::filter(container, [](typename T::value_type v) {  // move the result
        return v > 5;
    });
    T filterRet { 6, 7, 8, 9 };
    assert(filtered == filterRet);

    // map
    auto mapped = _::map(container, [](typename T::value_type v) {
        return v * 0;
    });
    vector<int> mapRet { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    assert(mapped == mapRet);

    auto mappedList = _::map<list>(container, [](typename T::value_type v) { // use list as result container
        return "item";
    });
    list<const char*> mapRetList { "item", "item", "item", "item", "item", "item", "item", "item", "item", "item"};
    assert(mappedList == mapRetList);

    // reduce
    sum = _::reduce(container, [](int memo, typename T::value_type v) {
        return memo + v; 
    }, 100.0); // convertible
    assert(sum == 145);

    cout << "[ok] test " << name << endl;
}

template<typename T> void
testMappedContainer(const string& name) {
    // assume key is string and value is number
    T container {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"x", 10}, {"y", 20}, {"z", 30}};

    // each
    _::each(container, [](typename T::mapped_type& v, typename T::key_type k) {
        ++v;
    });
    T eachRet {{"a", 2}, {"b", 3}, {"c", 4}, {"d", 5}, {"x", 11}, {"y", 21}, {"z", 31}};
    assert(container == eachRet);

    // all
    assert(_::all(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v >= 2;
    }));

    // any
    assert(_::any(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v > 30;
    }));

    // filter
    T filtered = _::filter(container, [](typename T::mapped_type v, typename T::key_type k) {  // move the result
        return v > 5;
    });
    T filterRet {{"x", 11}, {"y", 21}, {"z", 31}};
    assert(filtered == filterRet);

    // map
    auto mapped = _::map(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v * 0;
    });
    vector<int> mapRet { 0, 0, 0, 0, 0, 0, 0 };
    assert(mapped == mapRet);

    auto mappedList = _::map<list>(container, [](typename T::mapped_type v, typename T::key_type k) { // use list as result container
        return "item";
    });
    list<const char*> mapRetList { "item", "item", "item", "item", "item", "item", "item" };
    assert(mappedList == mapRetList);

    // reduce
    int sum = _::reduce(container, [](int memo, typename T::mapped_type v, typename T::key_type k) {
        return memo + v; 
    }, 100.0);
    assert(sum == 177);

    cout << "[ok] test " << name << endl;
}

template<typename T> void
testFixedLengthContainer(const string& name) {
    // assume value could be number
    T container = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // each
    int sum = 0;
    _::each(container, [&](int v) {
        sum += v;
    });
    assert(sum == 45); // just check sum

    // all
    assert(_::all(container, [](int v) {
        return v >= 0;
    }));

    // any
    assert(_::any(container, [](int v) {
        return v > 8;
    }));

    cout << "[ok] test " << name << endl;
}

int main() {
    testNonMappedContainer<string>("string");
    testNonMappedContainer<vector<int>>("vector");
    testNonMappedContainer<deque<int>>("deque");
    testNonMappedContainer<list<int>>("list");
    testNonMappedContainer<forward_list<int>>("forward_list");
    testNonMappedContainer<set<int>>("set");
    testNonMappedContainer<multiset<int>>("multiset");
    testNonMappedContainer<unordered_set<int>>("unordered_set");
    testNonMappedContainer<unordered_multiset<int>>("unordered_multiset");

    testMappedContainer<map<string, int>>("map");
    testMappedContainer<multimap<string, int>>("multimap");
    testMappedContainer<unordered_map<string, int>>("unordered_map");
    testMappedContainer<unordered_multimap<string, int>>("unordered_multimap");

    testFixedLengthContainer<int [10]>("c_array");
    testFixedLengthContainer<array<int, 10>>("array");
    testFixedLengthContainer<initializer_list<int>>("initializer_list");

    cout << "All tests passed." << endl;
    return 0;
}
