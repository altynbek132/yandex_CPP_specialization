#pragma once
#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

/**
 * first and second are interchangable
 * */
struct Neighbors {
    std::string first;
    std::string second;
    bool operator==(const Neighbors& rhs) const;
    bool operator!=(const Neighbors& rhs) const;
};

namespace std {
template <>
struct hash<Neighbors> {
    size_t operator()(const Neighbors& obj) const;
    hash<std::string> string_hash;
};
}  // namespace std