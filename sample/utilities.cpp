//
// Created by Addmin on 10.12.2020.
//
#include "utilities.h"
//
//template<typename First, typename Second>
//std::ostream &operator<<(std::ostream &out, const std::pair<First, Second> &p) {
//    return out << '(' << p.first << ',' << p.second << ')';
//}
//
//template<typename T>
//std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
//    return out << '[' << Join(v, ',') << ']';
//}
//
//template<typename Key, typename Value>
//std::ostream &operator<<(std::ostream &out, const std::map<Key, Value> &m) {
//    return out << '{' << Join(m, ',') << '}';
//}
//
//template<size_t n, typename... T>
//typename std::enable_if<(n >= sizeof...(T))>::type
//print_tuple(std::ostream &, const std::tuple<T...> &) {}
//
//template<size_t n, typename... T>
//typename std::enable_if<(n < sizeof...(T))>::type
//print_tuple(std::ostream &os, const std::tuple<T...> &tup) {
//    if (n != 0) {
//        os << ", ";
//    }
//    os << std::get<n>(tup);
//    print_tuple<n + 1>(os, tup);
//}
//
//template<typename... T>
//std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
//    os << "[";
//    print_tuple<0>(os, tup);
//    return os << "]";
//}
//
//template<typename Collection>
//std::string Join(const Collection &col, char sep) {
//    std::stringstream ss;
//    bool first = true;
//    for (const auto &i : col) {
//        if (!first) {
//            ss << sep;
//        }
//        first = false;
//        ss << i;
//    }
//    return ss.str();
//}

// utility functions
void txt() {
#ifdef MASLO
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

void ensure(std::istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(std::ios::failbit);
        throw std::exception();
    }
    input.ignore(1);
}

void ensure(std::istream &input) {
    if (!input) {
        throw std::exception();
    }
}

void ensure(bool state) {
    if (!state) {
        throw std::exception();
    }
}

std::stringstream stream_line(std::istream &input) {
    std::string line;
    while (line.empty() && !input.eof()) {
        getline(input, line);
    }
    std::stringstream input_stream(line);
    return input_stream;
}

void io_files(std::ifstream &in, const std::string &input, std::ofstream &out, const std::string &output) {
    in = std::ifstream(input);
    out = std::ofstream(output);
}
