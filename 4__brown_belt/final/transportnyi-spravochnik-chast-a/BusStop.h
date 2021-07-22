#pragma once
#include <bits/stdc++.h>
#include "Coordinate.h"
#include "utils.h"

using namespace std;

struct BusStop {
    string name;
    Coordinate coordinate;
};

namespace std {
template <>
struct hash<BusStop> {
    hash<string> string_hash;
    hash<Coordinate> Coordinate_hash;
    size_t operator()(const BusStop& obj) const;
};
}  // namespace std