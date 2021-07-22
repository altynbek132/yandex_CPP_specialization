#pragma once
#include "utils.h"

#include <bits/stdc++.h>
using namespace std;

struct Coordinate {
    double latitude;
    double longitude;
    double DistanceTo(const Coordinate& other ) const;
};

double DistanceBetween(const Coordinate& first, const Coordinate& second);

namespace std {
template <>
struct hash<Coordinate> {
    size_t operator()(const Coordinate& obj) const;
    hash<double> double_hash;
};
}  // namespace std
