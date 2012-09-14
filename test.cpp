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


template<typename T>
typename std::enable_if<!_::util::IsMappedContainer<T>::value, void>::type
testInputIt(const string& name) {
    // assume value could be number
    T init { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    T container = init; // reorder

    // each
    vector<int> eached;
    _::each(container, [&](typename T::value_type v) {
        eached.push_back(++v);
    });
    vector<int> eachRet { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    assert(eached == eachRet);

    // map
    auto mapped = _::map(container, [](typename T::value_type v) {
        return v * 2;
    });
    vector<int> mapRet { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
    assert(mapped == mapRet);

    auto mappedList = _::map<list>(container, [](typename T::value_type v) { // use list as result container
        return v * 2;
    });
    list<int> mapRetList { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
    assert(mappedList == mapRetList);

    // reduce
    auto sum = _::reduce(container, [](int memo, typename T::value_type v) {
        return memo + v; 
    }, 100.0); // convertible
    assert(sum == 145);

    // find
    auto target = _::find(container, [](typename T::value_type v) {
        return v == 5;
    });
    assert(*target == 5);

    // filter
    auto filtered = _::filter(container, [](typename T::value_type v) {
        return v > 5;
    });
    vector<typename T::value_type> filterRet { 6, 7, 8, 9 };
    assert(filtered == filterRet);

    // reject
    auto rejected = _::reject(container, [](typename T::value_type v) {
        return v <= 5;
    });
    vector<typename T::value_type> rejectRet { 6, 7, 8, 9 };
    assert(rejected == rejectRet);

    // all
    assert(_::all(container, [](typename T::value_type v) {
        return v >= 0;
    }));

    // any
    assert(_::any(container, [](typename T::value_type v) {
        return v > 8;
    }));

    cout << "[ok] testInputIt " << name << endl;
}

template<typename T>
typename std::enable_if<!_::util::IsMappedContainer<T>::value, void>::type
testBidirectionalIt(const string& name) {
    // assume value could be number
    T container { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // reduce right
    auto sum = _::reduceRight(container, [](int memo, typename T::value_type v) {
        return memo + v; 
    }, 100);
    assert(sum == 145);

    cout << "[ok] testBidirectionalIt " << name << endl;
}

template<typename T>
typename std::enable_if<_::util::IsMappedContainer<T>::value, void>::type
testInputIt(const string& name) {
    // assume key is string and value is number
    T container {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"x", 10}, {"y", 20}, {"z", 30}};

    // each
    _::each(container, [](typename T::mapped_type& v, typename T::key_type k) {
        ++v;
    });
    T eachRet {{"a", 2}, {"b", 3}, {"c", 4}, {"d", 5}, {"x", 11}, {"y", 21}, {"z", 31}};
    assert(container == eachRet);

    // map
    auto mapped = _::map(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v * 2;
    });
    vector<int> mapRet { 4, 6, 8, 10, 22, 42, 62 };
    sort(mapped.begin(), mapped.end()); // need sort to check
    assert(mapped == mapRet);

    auto mappedDq = _::map<deque>(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v * 2;
    });
    deque<int> mapRetDq { 4, 6, 8, 10, 22, 42, 62 };
    sort(mappedDq.begin(), mappedDq.end());
    assert(mappedDq == mapRetDq);

    // reduce
    auto sum = _::reduce(container, [](int memo, typename T::mapped_type v, typename T::key_type k) {
        return memo + v; 
    }, 100.0);
    assert(sum == 177);

    // find
    auto target = _::find(container, [](typename T::mapped_type v, typename T::key_type k) {
        return k == "x";
    });
    assert(*target == 11);

    // filter
    auto filtered = _::filter(container, [](typename T::mapped_type v, typename T::key_type k) {  // move the result
        return v > 5;
    });
    vector<typename T::mapped_type> filterRet {11, 21, 31};
    std::sort(filtered.begin(), filtered.end());
    assert(filtered == filterRet);

    // reject
    auto rejected = _::reject(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v <= 5;
    });
    vector<typename T::mapped_type> rejectRet { 11, 21, 31 };
    std::sort(rejected.begin(), rejected.end());
    assert(rejected == rejectRet);

    // all
    assert(_::all(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v >= 2;
    }));

    // any
    assert(_::any(container, [](typename T::mapped_type v, typename T::key_type k) {
        return v > 30;
    }));

    cout << "[ok] testInputIt " << name << endl;
}

template<typename T>
typename std::enable_if<_::util::IsMappedContainer<T>::value, void>::type
testBidirectionalIt(const string& name) {
    // assume key is string and value is number
    T container {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"x", 10}, {"y", 20}, {"z", 30}};

    // reduce right
    int sum = _::reduceRight(container, [](int memo, typename T::mapped_type v, typename T::key_type k) {
        return memo + v; 
    }, 100);
    assert(sum == 170);

    cout << "[ok] testBidirectionalIt " << name << endl;
}

template<typename T> void
testFixedLength(const string& name) {
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
    testInputIt<string>("string");
    testInputIt<vector<int>>("vector");
    testInputIt<deque<int>>("deque");
    testInputIt<list<int>>("list");
    testInputIt<forward_list<int>>("forward_list");
    testInputIt<set<int>>("set");
    testInputIt<multiset<int>>("multiset");
    testInputIt<unordered_set<int>>("unordered_set");
    testInputIt<unordered_multiset<int>>("unordered_multiset");
    testInputIt<map<string, int>>("map");
    testInputIt<multimap<string, int>>("multimap");
    testInputIt<unordered_map<string, int>>("unordered_map");
    testInputIt<unordered_multimap<string, int>>("unordered_multimap");

    testBidirectionalIt<string>("string");
    testBidirectionalIt<vector<int>>("vector");
    testBidirectionalIt<deque<int>>("deque");
    testBidirectionalIt<list<int>>("list");
    testBidirectionalIt<set<int>>("set");
    testBidirectionalIt<multiset<int>>("multiset");
    testBidirectionalIt<map<string, int>>("map");
    testBidirectionalIt<multimap<string, int>>("multimap");

    testFixedLength<int [10]>("c_array");
    testFixedLength<array<int, 10>>("array");
    testFixedLength<initializer_list<int>>("initializer_list");

    cout << "All tests passed." << endl;
    return 0;
}

    
