//
// Created by Addmin on 10.12.2020.
//

// #include <bits/stdc++.h>
//
//#include <cstdlib>
//#include <iostream>
//
//#include <algorithm>
//#include <deque>
//#include <iterator>
//#include <map>
//#include <numeric>
//#include <set>
//#include <sstream>
//#include <string>
//#include <tuple>
//#include <utility>
//#include <vector>
//
//#include <iomanip>
//#include <fstream>
//
//#include <type_traits>
//
//#include <numeric>
//#include <limits>
//
//#include <cassert>
//#include <random>



#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <fstream>


template<typename First, typename Second>
std::ostream &operator<<(std::ostream &out, const std::pair<First, Second> &p);

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v);

template<typename Key, typename Value>
std::ostream &operator<<(std::ostream &out, const std::map<Key, Value> &m);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &);

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup);

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup);

template<typename Collection>
std::string Join(const Collection &col, char sep);




template<typename First, typename Second>
std::ostream &operator<<(std::ostream &out, const std::pair<First, Second> &p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    return out << '[' << Join(v, ',') << ']';
}

template<typename Key, typename Value>
std::ostream &operator<<(std::ostream &out, const std::map<Key, Value> &m) {
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

template<typename Collection>
std::string Join(const Collection &col, char sep) {
    std::stringstream ss;
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




// utility functions
void txt();

void ensure(std::istream &input, char expected);

void ensure(std::istream &input);

void ensure(bool state);

std::stringstream stream_line(std::istream &input);

void io_files(std::ifstream &in, const std::string &input, std::ofstream &out, const std::string &output);
