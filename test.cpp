#include "underscore.h"

#include <iostream>
#include <sstream>
#include <cassert>

#include <array>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set> // multiset
#include <unordered_set> // unordered_multiset
#include <map> // multimap
#include <unordered_map> // unordered_multimap

using namespace std;

class Data {
public:
    Data(int i = 0) : i_(i) { }
    void set(int i) { i_ = i; }
    int get() const { return i_; }

    bool operator < (const Data& d) const {
        return i_ < d.i_;
    }

    bool operator == (const Data& d) const {
        return i_ == d.i_;
    }

    int i_;
};

template<>
class hash<Data> {
public:
    size_t operator()(const Data& d) const {
        return std::hash<int>()(d.get());
    }
};

class Tracer {
public:
    Tracer(const string& info, bool supported = true) : info_(info), supported_(supported) {
        cout << "test " << suit_ << " : " << info_ << " ";
    }
    ~Tracer() {
        if (supported_) {
            cout << "[ok]" << endl;
        } else {
            cout << "[not supported]" << endl;
        }
    }

    static string suit_;

private:
    string info_;
    bool supported_;
};
string Tracer::suit_;

string
itoa(int i) {
    ostringstream o;
    o << i;
    return o.str();
}

void
test_each() {
    Tracer::suit_ = "each";

    {
        Tracer t("C-style array");
        int data[]   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int expect[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [](int& v) {
            ++v;
        });
        for (int i = 0; i != 10; ++i) {
            assert(data[i] == expect[i]);
        }
    }

    {
        Tracer t("array");
        array<int, 10> data   = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        array<int, 10> expect = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [](int& v) {
            ++v;
        });
        assert(data == expect);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect("HELLO WORLD!");
        _::each(data, [](char& v) {
            if (v >= 'a' && v <= 'z') {
                v -= 32;
            }
        });
        assert(data == expect);
    }

    {
        Tracer t("vector");
        vector<int> data   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [](int& v) {
            ++v;
        });
        assert(data == expect);
    }

    {
        Tracer t("deque");
        deque<int> data   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        deque<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [](int& v) {
            ++v;
        });
        assert(data == expect);
    }

    {
        Tracer t("list");
        list<int> data   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        list<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [](int& v) {
            ++v;
        });
        assert(data == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        forward_list<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [](int& v) {
            ++v;
        });
        assert(data == expect);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<int> result;
        vector<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        _::each(data, [&](int v) {
            result.push_back(++v);
        });
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        vector<int> result;
        vector<int> expect { 1, 1, 3, 3, 5, 5, 7, 7, 9, 9 };
        _::each(data, [&](int v) {
            result.push_back(++v);
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<int> result;
        vector<int> expect { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        _::each(data, [&](int v) {
            result.push_back(++v);
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        vector<int> result;
        vector<int> expect { 9, 9, 7, 7, 5, 5, 3, 3, 1, 1 };
        _::each(data, [&](int v) {
            result.push_back(++v);
        });
        assert(result == expect);
    }

    {
        Tracer t("map");
        map<int, string> data   { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        map<int, string> expect { {1, "aa"}, {2, "bb"}, {3, "cc"}, {4, "dd"}, {10, "xx"}, {20, "yy"}, {30, "zz"} };
        _::each(data, [](pair<const int, string>& v) {
            v.second += v.second;
        });
        assert(data == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data   { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        multimap<int, string> expect { {2, "aa"}, {2, "bb"}, {4, "cc"}, {4, "dd"}, {10, "xx"}, {10, "yy"} };
        _::each(data, [](pair<const int, string>& v) {
            v.second += v.second;
        });
        assert(data == expect);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data   { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        unordered_map<int, string> expect { {1, "aa"}, {2, "bb"}, {3, "cc"}, {4, "dd"}, {10, "xx"}, {20, "yy"}, {30, "zz"} };
        _::each(data, [](pair<const int, string>& v) {
            v.second += v.second;
        });
        assert(data == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data   { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        unordered_multimap<int, string> expect { {2, "aa"}, {2, "bb"}, {4, "cc"}, {4, "dd"}, {10, "xx"}, {10, "yy"} };
        _::each(data, [](pair<const int, string>& v) {
            v.second += v.second;
        });
        assert(data == expect);
    }
}

void
test_map() {
    Tracer::suit_ = "map";

    {
        Tracer t("C-style array");
        int data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        vector<string> result = _::map(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        vector<string> result = _::map(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect("HELLO WORLD!");
        string result = _::map<basic_string>(data, [](char v) {
            return v >= 'a' && v <= 'z' ? static_cast<char>(v - 32) : v;
        });
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        vector<string> result = _::map(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        deque<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        deque<string> result = _::map<deque>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        list<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        list<string> result = _::map<list>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        forward_list<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        forward_list<string> result = _::map<forward_list>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        set<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        set<string> result = _::map<set>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        multiset<string> expect { "0", "0", "2", "2", "4", "4", "6", "6", "8", "8" };
        multiset<string> result = _::map<multiset>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        unordered_set<string> expect { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        unordered_set<string> result = _::map<unordered_set>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        unordered_multiset<string> expect { "0", "0", "2", "2", "4", "4", "6", "6", "8", "8" };
        unordered_multiset<string> result = _::map<unordered_multiset>(data, [](int v) {
            return itoa(v);
        });
        assert(result == expect);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        vector<string> expect { "a", "b", "c", "d", "x", "y", "z" };
        vector<string> result = _::map(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        vector<string> expect { "a", "b", "c", "d", "x", "y"};
        vector<string> result = _::map(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        list<string> expect { "z", "y", "x", "d", "c", "b", "a" };
        list<string> result = _::map<list>(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        list<string> expect { "x", "y", "c", "d", "a", "b" };
        list<string> result = _::map<list>(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result == expect);
    }
}

void
test_reduce() {
    Tracer::suit_ = "reduce";

    {
        Tracer t("C-style array");
        int data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int result = _::reduce(data, [](int memo, int v) {
            return memo + v;
        }, 100.0);
        assert(result == 145);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int result = _::reduce(data, [](int memo, int v) {
            return memo + v;
        }, 100);
        assert(result == 145);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect("HELLO WORLD!");
        string result = _::reduce(data, [](string memo, char v) {
            return memo + string(1, v >= 'a' && v <= 'z' ? v - 32 : v);
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "0123456789";
        string result = _::reduce(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "0123456789";
        string result = _::reduce(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "0123456789";
        string result = _::reduce(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "0123456789";
        string result = _::reduce(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "0123456789";
        string result = _::reduce(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<string> data { "0", "0", "2", "2", "4", "4", "6", "6", "8", "8" };
        string expect = "0022446688";
        string result = _::reduce(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int result = _::reduce(data, [](int memo, int v) {
            return memo + v;
        }, 100);
        assert(result == 145);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        int result = _::reduce(data, [](int memo, int v) {
            return memo + v;
        }, 100);
        assert(result == 140);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        string expect = "abcdxyz";
        string result = _::reduce(data, [](string memo, const pair<const int, string>& v) {
            return memo + v.second;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        string expect = "abcdxy";
        string result = _::reduce(data, [](string memo, const pair<const int, string>& v) {
            return memo + v.second;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        int result = _::reduce(data, [](int memo, const pair<const int, string>& v) {
            return memo + v.first;
        }, 0);
        assert(result == 70);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        int result = _::reduce(data, [](int memo, const pair<const int, string>& v) {
            return memo + v.first;
        }, 0);
        assert(result == 32);
    }
}

void
test_reduceRight() {
    Tracer::suit_ = "reduceRight";

    {
        Tracer t("C-style array");
        int data[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int result = _::reduceRight(data, [](int memo, int v) {
            return memo + v;
        }, 100.0);
        assert(result == 145);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int result = _::reduceRight(data, [](int memo, int v) {
            return memo + v;
        }, 100);
        assert(result == 145);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect("!DLROW OLLEH");
        string result = _::reduceRight(data, [](string memo, char v) {
            return memo + string(1, v >= 'a' && v <= 'z' ? v - 32 : v);
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "9876543210";
        string result = _::reduceRight(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "9876543210";
        string result = _::reduceRight(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "9876543210";
        string result = _::reduceRight(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("forward_list", false);
    }

    {
        Tracer t("set");
        set<string> data { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        string expect = "9876543210";
        string result = _::reduceRight(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<string> data { "0", "0", "2", "2", "4", "4", "6", "6", "8", "8" };
        string expect = "8866442200";
        string result = _::reduceRight(data, [](string memo, const string& v) {
            return memo + v;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("unordered_set", false);
    }

    {
        Tracer t("unordered_multiset", false);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        string expect = "zyxdcba";
        string result = _::reduceRight(data, [](string memo, const pair<const int, string>& v) {
            return memo + v.second;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        string expect = "yxdcba";
        string result = _::reduceRight(data, [](string memo, const pair<const int, string>& v) {
            return memo + v.second;
        }, string());
        assert(result == expect);
    }

    {
        Tracer t("unordered_map", false);
    }

    {
        Tracer t("unordered_multimap", false);
    }
}

void
test_find() {
    Tracer::suit_ = "find";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int* result = _::find(data, [](int v) {
            return v % 2 == 0;
        });
        assert(*result == 2);

        result = _::find(data, [](int v) {
            return v > 9;
        });
        assert(result == end(data));
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::find(data, [](char v) {
            return v == 'w';
        });
        assert(*result == 'w');
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::find(data, [](int v) {
            return v > 5;
        });
        assert(*result == 6);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::find(data, [](int v) {
            return v == 5;
        });
        assert(*result == 5);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::find(data, [](int v) {
            return v == 2;
        });
        assert(*result == 2);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::find(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result->first == 10);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::find(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result->first == 10);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::find(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result->first == 10);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::find(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result->first == 10);
    }
}

void
test_filter() {
    Tracer::suit_ = "filter";

    {
        Tracer t("C-style array", false);
    }

    {
        Tracer t("array", false);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect("lloworl");
        string result = _::filter(data, [](char v) {
            return v > 'h';
        });
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<int> expect { 6, 7, 8, 9 };
        vector<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        deque<int> expect { 6, 7, 8, 9 };
        deque<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        list<int> expect { 6, 7, 8, 9 };
        list<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        forward_list<int> expect { 6, 7, 8, 9 };
        forward_list<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        set<int> expect { 6, 7, 8, 9 };
        set<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        multiset<int> expect { 6, 6, 8, 8 };
        multiset<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        unordered_set<int> expect { 6, 7, 8, 9 };
        unordered_set<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        unordered_multiset<int> expect { 6, 6, 8, 8 };
        unordered_multiset<int> result = _::filter(data, [](int v) {
            return v > 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        map<int, string> expect { {10, "x"}, {20, "y"}, {30, "z"} };
        map<int, string> result = _::filter(data, [](const pair<const int, string>& v) {
            return v.first >= 10;
        });
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        multimap<int, string> expect { {10, "x"}, {10, "y"} };
        multimap<int, string> result = _::filter(data, [](const pair<const int, string>& v) {
            return v.first >= 10;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        unordered_map<int, string> expect { {10, "x"}, {20, "y"}, {30, "z"} };
        unordered_map<int, string> result = _::filter(data, [](const pair<const int, string>& v) {
            return v.first >= 10;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        unordered_multimap<int, string> expect { {10, "x"}, {10, "y"} };
        unordered_multimap<int, string> result = _::filter(data, [](const pair<const int, string>& v) {
            return v.first >= 10;
        });
        assert(result == expect);
    }
}

void
test_reject() {
    Tracer::suit_ = "reject";

    {
        Tracer t("C-style array", false);
    }

    {
        Tracer t("array", false);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect("lloworl");
        string result = _::reject(data, [](char v) {
            return v <= 'h';
        });
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<int> expect { 6, 7, 8, 9 };
        vector<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        deque<int> expect { 6, 7, 8, 9 };
        deque<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        list<int> expect { 6, 7, 8, 9 };
        list<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        forward_list<int> expect { 6, 7, 8, 9 };
        forward_list<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        set<int> expect { 6, 7, 8, 9 };
        set<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        multiset<int> expect { 6, 6, 8, 8 };
        multiset<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        unordered_set<int> expect { 6, 7, 8, 9 };
        unordered_set<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        unordered_multiset<int> expect { 6, 6, 8, 8 };
        unordered_multiset<int> result = _::reject(data, [](int v) {
            return v <= 5;
        });
        assert(result == expect);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        map<int, string> expect { {10, "x"}, {20, "y"}, {30, "z"} };
        map<int, string> result = _::reject(data, [](const pair<const int, string>& v) {
            return v.first < 10;
        });
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        multimap<int, string> expect { {10, "x"}, {10, "y"} };
        multimap<int, string> result = _::reject(data, [](const pair<const int, string>& v) {
            return v.first < 10;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        unordered_map<int, string> expect { {10, "x"}, {20, "y"}, {30, "z"} };
        unordered_map<int, string> result = _::reject(data, [](const pair<const int, string>& v) {
            return v.first < 10;
        });
        assert(result == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        unordered_multimap<int, string> expect { {10, "x"}, {10, "y"} };
        unordered_multimap<int, string> result = _::reject(data, [](const pair<const int, string>& v) {
            return v.first < 10;
        });
        assert(result == expect);
    }
}

void
test_every() {
    Tracer::suit_ = "every";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v > 0;
        });
        assert(result);

        result = _::every(data, [](int v) {
            return v > 1;
        });
        assert(!result);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::every(data, [](char v) {
            return v >= ' ';
        });
        assert(result);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::every(data, [](int v) {
            return v >= 0;
        });
        assert(result);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::every(data, [](const pair<const int, string>& v) {
            return v.second >= "a";
        });
        assert(result);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::every(data, [](const pair<const int, string>& v) {
            return v.second >= "a";
        });
        assert(result);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::every(data, [](const pair<const int, string>& v) {
            return v.second >= "a";
        });
        assert(result);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::every(data, [](const pair<const int, string>& v) {
            return v.second >= "a";
        });
        assert(result);
    }
}

void
test_some() {
    Tracer::suit_ = "some";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 0;
        });
        assert(result);

        result = _::some(data, [](int v) {
            return v > 9;
        });
        assert(!result);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::some(data, [](char v) {
            return v == 'w';
        });
        assert(result);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::some(data, [](int v) {
            return v > 5;
        });
        assert(result);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::some(data, [](int v) {
            return v == 5;
        });
        assert(result);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::some(data, [](int v) {
            return v == 2;
        });
        assert(result);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::some(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::some(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::some(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::some(data, [](const pair<const int, string>& v) {
            return v.second == "x";
        });
        assert(result);
    }
}

void
test_contains() {
    Tracer::suit_ = "contains";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);

        result = _::contains(data, 0);
        assert(!result);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::contains(data, 'r');
        assert(result);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::contains(data, 4);
        assert(result);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::contains(data, 3);
        assert(result);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::contains(data, 4);
        assert(result);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::contains(data, pair<const int, string>(4, "d"));
        assert(result);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::contains(data, pair<const int, string>(4, "d"));
        assert(result);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::contains(data, pair<const int, string>(4, "d"));
        assert(result);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::contains(data, pair<const int, string>(4, "d"));
        assert(result);
    }
}

void
test_invoke() {
    Tracer::suit_ = "invoke";

    {
        Tracer t("C-style array");
        Data data[10];
        _::invoke(data, &Data::set, 5);
        auto result = _::invoke(data, &Data::get);
        for (auto& i : result) {
            assert(i == 5);
        }
    }

    {
        Tracer t("array");
        array<Data, 10> data;
        _::invoke(data, &Data::set, 5);
        auto result = _::invoke(data, &Data::get);
        for (auto& i : result) {
            assert(i == 5);
        }
    }

    {
        Tracer t("string", false);
    }

    {
        Tracer t("vector");
        vector<Data> data(10);
        _::invoke(data, &Data::set, 5);
        auto result = _::invoke(data, &Data::get);
        for (auto& i : result) {
            assert(i == 5);
        }
    }

    {
        Tracer t("deque");
        deque<Data> data(10);
        _::invoke(data, &Data::set, 5);
        auto result = _::invoke<deque>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 5);
        }
    }

    {
        Tracer t("list");
        list<Data> data(10);
        _::invoke(data, &Data::set, 5);
        auto result = _::invoke<list>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 5);
        }
    }

    {
        Tracer t("forward_list");
        forward_list<Data> data(10);
        _::invoke(data, &Data::set, 5);
        auto result = _::invoke<forward_list>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 5);
        }
    }

    {
        Tracer t("set");
        set<Data> data { Data(), Data(), Data(), Data() };
        auto result = _::invoke<set>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("multiset");
        multiset<Data> data { Data(1), Data(1), Data(1), Data(1) };
        auto result = _::invoke<multiset>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 1);
        }
    }

    {
        Tracer t("unordered_set");
        unordered_set<Data> data { Data(2), Data(2), Data(2), Data(2) };
        auto result = _::invoke<unordered_set>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 2);
        }
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<Data> data { Data(3), Data(3), Data(3), Data(3) };
        auto result = _::invoke<unordered_multiset>(data, &Data::get);
        for (auto& i : result) {
            assert(i == 3);
        }
    }

    {
        Tracer t("map", false);
    }

    {
        Tracer t("multimap", false);
    }

    {
        Tracer t("unordered_map", false);
    }

    {
        Tracer t("unordered_multimap", false);
    }
}

void
test_pluck() {
    Tracer::suit_ = "pluck";

    {
        Tracer t("C-style array");
        Data data[10];
        auto result = _::pluck(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("array");
        array<Data, 10> data;
        auto result = _::pluck(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("string", false);
    }

    {
        Tracer t("vector");
        vector<Data> data(10);
        auto result = _::pluck(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("deque");
        deque<Data> data(10);
        auto result = _::pluck<deque>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("list");
        list<Data> data(10);
        auto result = _::pluck<list>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("forward_list");
        forward_list<Data> data(10);
        auto result = _::pluck<forward_list>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("set");
        set<Data> data { Data(), Data(), Data(), Data() };
        auto result = _::pluck<set>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 0);
        }
    }

    {
        Tracer t("multiset");
        multiset<Data> data { Data(1), Data(1), Data(1), Data(1) };
        auto result = _::pluck<multiset>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 1);
        }
    }

    {
        Tracer t("unordered_set");
        unordered_set<Data> data { Data(2), Data(2), Data(2), Data(2) };
        auto result = _::pluck<unordered_set>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 2);
        }
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<Data> data { Data(3), Data(3), Data(3), Data(3) };
        auto result = _::pluck<unordered_multiset>(data, &Data::i_);
        for (auto& i : result) {
            assert(i == 3);
        }
    }

    {
        Tracer t("map", false);
    }

    {
        Tracer t("multimap", false);
    }

    {
        Tracer t("unordered_map", false);
    }

    {
        Tracer t("unordered_multimap", false);
    }
}

void
test_max() {
    Tracer::suit_ = "max";

    {
        Tracer t("C-style array");
        Data data[] { Data(1), Data(2), Data(3), Data(4) };
        Data* result = _::max(data, [](const Data& d) {
            return d.i_;
        });
        assert(result->get() == 4);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::max(data);
        assert(*result == 'w');
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::max(data);
        assert(*result == 8);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::max(data);
        assert(*result == 9);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::max(data);
        assert(*result == 8);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::max(data, [](const pair<const int, string>& v) {
            return v.first;
        });
        assert(result->second == "z");
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::max(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result->first == 10);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::max(data, [](const pair<const int, string>& v) {
            return v.first;
        });
        assert(result->second == "z");
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::max(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result->first == 10);
    }
}

void
test_min() {
    Tracer::suit_ = "min";

    {
        Tracer t("C-style array");
        Data data[] { Data(1), Data(2), Data(3), Data(4) };
        Data* result = _::min(data, [](const Data& d) {
            return d.i_;
        });
        assert(result->get() == 1);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::min(data);
        assert(*result == ' ');
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::min(data);
        assert(*result == 0);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::min(data, [](const pair<const int, string>& v) {
            return v.first;
        });
        assert(result->second == "a");
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::min(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result->first == 2);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::min(data, [](const pair<const int, string>& v) {
            return v.first;
        });
        assert(result->second == "a");
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::min(data, [](const pair<const int, string>& v) {
            return v.second;
        });
        assert(result->first == 2);
    }
}

void
test_sortBy() {
    Tracer::suit_ = "sortBy";

    {
        Tracer t("C-style array", false);
    }

    {
        Tracer t("array");
        array<Data, 6> data   = { Data(4), Data(1), Data(3), Data(2), Data(0), Data(5) };
        array<Data, 6> expect = { Data(0), Data(1), Data(2), Data(3), Data(4), Data(5) };
        auto result = _::sortBy(data, [](const Data& v) {
            return v.i_;
        });
        assert(result == expect);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string expect(" !dehllloorw");
        auto result = _::sortBy(data, [](char v) {
            return v;
        });
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data   = { 9, 1, 0, 3, 2, 5, 6, 4, 8, 7 };
        vector<int> expect = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::sortBy(data, [](int v) {
            return v;
        });
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data   = { 9, 1, 0, 3, 2, 5, 6, 4, 8, 7 };
        deque<int> expect = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::sortBy(data, [](int v) {
            return v;
        });
        assert(result == expect);
    }

    {
        Tracer t("list", false);
    }

    {
        Tracer t("forward_list", false);
    }

    {
        Tracer t("set", false);
    }

    {
        Tracer t("multiset", false);
    }

    {
        Tracer t("unordered_set", false);
    }

    {
        Tracer t("unordered_multiset", false);
    }

    {
        Tracer t("map", false);
    }

    {
        Tracer t("multimap", false);
    }

    {
        Tracer t("unordered_map", false);
    }

    {
        Tracer t("unordered_multimap", false);
    }
}

void
test_groupBy() {
    Tracer::suit_ = "groupBy";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 0}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("string");
        string data("Hello World!");
        auto result = _::groupBy(data, [](char i) {
            return i > 90;
        });
        multimap<bool, char> expect { {false, 'H'}, {false, ' '}, {false, 'W'}, {false, '!'},
            {true, 'e'}, {true, 'l'}, {true, 'l'}, {true, 'o'}, {true, 'o'}, {true, 'r'}, {true, 'l'}, {true, 'd'} };
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 0}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 0}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 0}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 0}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 3}, {false, 5}, {false, 7}, {false, 9}, {true, 0}, {true, 2}, {true, 4}, {true, 6}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 1}, {false, 1}, {false, 3}, {false, 3}, {true, 0}, {true, 0}, {true, 2}, {true, 2}, {true, 4}, {true, 4} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 9}, {false, 7}, {false, 5}, {false, 3}, {false, 1}, {true, 8}, {true, 6}, {true, 4}, {true, 2}, {true, 0} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4 };
        auto result = _::groupBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        multimap<bool, int> expect { {false, 3}, {false, 3}, {false, 1}, {false, 1}, {true, 4}, {true, 4}, {true, 2}, {true, 2}, {true, 0}, {true, 0} };
        assert(result == expect);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "xx"}, {20, "yy"}, {30, "zz"} };
        auto result = _::groupBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        multimap<bool, pair<const int, string>> expect { {false, {1, "a"}}, {false, {2, "b"}}, {false, {3, "c"}}, {false, {4, "d"}},
            {true, {10, "xx"}}, {true, {20, "yy"}}, {true, {30, "zz"}} };
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {1, "a"}, {1, "b"}, {2, "c"}, {2, "d"}, {10, "xx"}, {10, "yy"} };
        auto result = _::groupBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        multimap<bool, pair<const int, string>> expect { {false, {1, "a"}}, {false, {1, "b"}}, {false, {2, "c"}}, {false, {2, "d"}},
            {true, {10, "xx"}}, {true, {10, "yy"}} };
        assert(result == expect);
    }
    
    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "xx"}, {20, "yy"}, {30, "zz"} };
        auto result = _::groupBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        multimap<bool, pair<const int, string>> expect { {false, {4, "d"}}, {false, {3, "c"}}, {false, {2, "b"}}, {false, {1, "a"}}, 
            {true, {30, "zz"}}, {true, {20, "yy"}}, {true, {10, "xx"}} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {1, "a"}, {1, "b"}, {2, "c"}, {2, "d"}, {10, "xx"}, {10, "yy"} };
        auto result = _::groupBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        multimap<bool, pair<const int, string>> expect { {false, {2, "c"}}, {false, {2, "d"}}, {false, {1, "a"}}, {false, {1, "b"}}, 
            {true, {10, "xx"}}, {true, {10, "yy"}} };
        assert(result == expect);
    }
}

void
test_countBy() {
    Tracer::suit_ = "countBy";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0 ? "even" : "odd";
        });
        map<const char*, size_t> expect { {"odd", 5}, {"even", 4} };
        assert(result == expect);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("string");
        string data("Hello World!");
        auto result = _::countBy(data, [](char i) {
            return i > 90;
        });
        map<bool, size_t> expect { {false, 4}, {true, 8} };
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 4}, {true, 6} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 5}, {true, 5} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4 };
        auto result = _::countBy(data, [](const int& i) {
            return i % 2 == 0;
        });
        map<bool, size_t> expect { {false, 4}, {true, 6} };
        assert(result == expect);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "xx"}, {20, "yy"}, {30, "zz"} };
        auto result = _::countBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        map<bool, size_t> expect { {false, 4}, {true, 3} };
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {1, "a"}, {1, "b"}, {2, "c"}, {2, "d"}, {10, "xx"}, {10, "yy"} };
        auto result = _::countBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        map<bool, size_t> expect { {false, 4}, {true, 2} };
        assert(result == expect);
    }
    
    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "xx"}, {20, "yy"}, {30, "zz"} };
        auto result = _::countBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        map<bool, size_t> expect { {false, 4}, {true, 3} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {1, "a"}, {1, "b"}, {2, "c"}, {2, "d"}, {10, "xx"}, {10, "yy"} };
        auto result = _::countBy(data, [](const pair<const int, string>& i) {
            return i.second.size() > 1;
        });
        map<bool, size_t> expect { {false, 4}, {true, 2} };
        assert(result == expect);
    }
}

void
test_shuffle() {
    Tracer::suit_ = "shuffle";

    {
        Tracer t("C-style array", false);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::shuffle(data);
        assert(result != data);
    }

    {
        Tracer t("string");
        string data("hello world!");
        string result = _::shuffle(data);
        assert(result != data);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<int> result = _::shuffle(data);
        assert(result != data);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        deque<int> result = _::shuffle(data);
        assert(result != data);
    }

    {
        Tracer t("list", false);
    }

    {
        Tracer t("forward_list", false);
    }

    {
        Tracer t("set", false);
    }

    {
        Tracer t("multiset", false);
    }

    {
        Tracer t("unordered_set", false);
    }

    {
        Tracer t("unordered_multiset", false);
    }

    {
        Tracer t("map", false);
    }

    {
        Tracer t("multimap", false);
    }

    {
        Tracer t("unordered_map", false);
    }

    {
        Tracer t("unordered_multimap", false);
    }
}

void
test_toArray() {
    Tracer::suit_ = "toArray";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray(data);
        vector<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
        auto result = _::toArray<list>(data);
        list<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
        assert(result == expect);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::toArray<list>(data);
        list<char> expect { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
        assert(result == expect);
    }

    {
        Tracer t("vector");
        vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray(data);
        vector<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("deque");
        deque<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray<deque>(data);
        deque<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("list");
        list<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray(data);
        vector<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray<list>(data);
        list<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("set");
        set<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray<forward_list>(data);
        forward_list<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("multiset");
        multiset<int> data = { 1, 1, 3, 3, 5, 5, 7, 7 };
        auto result = _::toArray<multiset>(data);
        multiset<int> expect { 1, 1, 3, 3, 5, 5, 7, 7 };
        assert(result == expect);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::toArray<set>(data);
        set<int> expect { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        assert(result == expect);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data = { 1, 1, 3, 3, 5, 5, 7, 7 };
        auto result = _::toArray<multiset>(data);
        multiset<int> expect { 1, 1, 3, 3, 5, 5, 7, 7 };
        assert(result == expect);
    }

    
    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::toArray(data);
        vector<pair<const int, string>> expect { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        assert(result == expect);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::toArray(data);
        vector<pair<const int, string>> expect { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::toArray<list>(data);
        list<pair<const int, string>> expect { {30, "z"}, {20, "y"}, {10, "x"}, {4, "d"}, {3, "c"}, {2, "b"}, {1, "a"} };
        assert(result == expect);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::toArray<list>(data);
        list<pair<const int, string>> expect { {10, "x"}, {10, "y"}, {4, "c"}, {4, "d"}, {2, "a"}, {2, "b"} };
        assert(result == expect);
    }
}

void
test_size() {
    Tracer::suit_ = "size";

    {
        Tracer t("C-style array");
        int data[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 9);
    }

    {
        Tracer t("array");
        array<int, 10> data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("string");
        string data("hello world!");
        auto result = _::size(data);
        assert(result == 12);
    }

    {
        Tracer t("vector");
        vector<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("deque");
        deque<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("list");
        list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("forward_list");
        forward_list<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("set");
        set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("multiset");
        multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("unordered_set");
        unordered_set<int> data { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("unordered_multiset");
        unordered_multiset<int> data { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8 };
        auto result = _::size(data);
        assert(result == 10);
    }

    {
        Tracer t("map");
        map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::size(data);
        assert(result == 7);
    }

    {
        Tracer t("multimap");
        multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::size(data);
        assert(result == 6);
    }

    {
        Tracer t("unordered_map");
        unordered_map<int, string> data { {1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {10, "x"}, {20, "y"}, {30, "z"} };
        auto result = _::size(data);
        assert(result == 7);
    }

    {
        Tracer t("unordered_multimap");
        unordered_multimap<int, string> data { {2, "a"}, {2, "b"}, {4, "c"}, {4, "d"}, {10, "x"}, {10, "y"} };
        auto result = _::size(data);
        assert(result == 6);
    }
}


int main() {
    test_each();
    test_map();
    test_reduce();
    test_reduceRight();
    test_find();
    test_filter();
    test_reject();
    test_every();
    test_some();
    test_contains();
    test_invoke();
    test_pluck();
    test_max();
    test_min();
    test_sortBy();
    test_groupBy();
    test_countBy();
    test_shuffle();
    test_toArray();
    test_size();

    cout << "All tests passed." << endl;
    return 0;
}


