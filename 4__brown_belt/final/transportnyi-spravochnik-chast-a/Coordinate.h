#pragma once
#include <bits/stdc++.h>
#include "utils.h"

struct Coordinate {
    double latitude;
    double longitude;
    double DistanceTo(const Coordinate& other) const;
};

double DistanceBetween(const Coordinate& first, const Coordinate& second);

namespace std {
template <>
struct hash<Coordinate> {
    size_t operator()(const Coordinate& obj) const;
    std::hash<double> double_hash;
};
}  // namespace std
