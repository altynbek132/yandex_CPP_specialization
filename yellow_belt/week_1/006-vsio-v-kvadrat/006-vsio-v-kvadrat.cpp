// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

#include <type_traits>

#include <numeric>
//#include <limits>

using namespace std;

#ifdef MASLO
// ========= Definitions
template<typename Collection>
string Join(const Collection &col, char sep);
template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p);
template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v);
template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &);
template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup);
template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup);

// ========= Implementations
template<typename Collection>
string Join(const Collection &col, char sep) {
    stringstream ss;
    bool first = true;
    for (const auto &i : col) {
        if (!first) {
            ss << sep;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    return out << '[' << Join(v, ',') << ']';
}

template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
    return out << '{' << Join(m, ',') << '}';
}


template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup) {
    if (n != 0) {
        os << ", ";
    }
    os << std::get<n>(tup);
    print_tuple<n + 1>(os, tup);
}

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

#endif


void txt() {
    const char *maslo = std::getenv("maslo");
    if (!maslo) {
        return;
    }
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

void ensure(istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(ios::failbit);
        throw exception();
    }
    input.ignore(1);
}

void ensure(istream &input) {
    if (!input) {
        throw exception();
    }
}

void ensure(bool state) {
    if (!state) {
        throw exception();
    }
}

stringstream stream_line(istream &input) {
    string line;
    while (line.empty() && !input.eof()) {
        getline(input, line);
    }
    stringstream input_stream(line);
    return input_stream;
}

void io_files(ifstream &in, const string &input, ofstream &out, const string &output) {
    in = ifstream(input);
    out = ofstream(output);
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

// ==================================

template<typename T>
T Sqr(T num);
template<typename T>
vector<T> Sqr(vector<T> v);
template<typename K, typename V>
map<K, V> Sqr(map<K, V> m);
template<typename F, typename S>
pair<F, S> Sqr(pair<F, S> p);

template<typename T>
T Sqr(T num) {
    return num * num;
}

template<typename T>
vector<T> Sqr(vector<T> v) {
    for (auto &val : v) {
        val = Sqr(val);
    }
    return v;
}

template<typename K, typename V>
map<K, V> Sqr(map<K, V> m) {
    for (auto &[key, val] : m) {
        val = Sqr(val);
    }
    return m;
}

template<typename F, typename S>
pair<F, S> Sqr(pair<F, S> p) {
    auto&[a, b]   = p;
    a = Sqr(a);
    b = Sqr(b);
    return p;
}
// ==================================

int main() {
    txt();
    ifstream in;
    ofstream out;
    io_files(in, "input.txt", out, "output.txt");
    // ================================================================
    
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;
    
    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    
    return 0;
}
