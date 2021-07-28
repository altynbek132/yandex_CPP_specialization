#pragma once
#include <bits/stdc++.h>
#include <ostream>
#include "Coordinate.h"
#include "DistanceToNeighborStop.h"

struct BusStop {
    std::string name;
    Coordinate coordinate;
    std::vector<DistanceToNeighborStop> distances_to_neighbor_stops;

    friend std::ostream& operator<<(std::ostream& os, const BusStop& stop);
};

namespace std {
template <>
struct hash<BusStop> {
    std::hash<std::string> string_hash;
    std::hash<Coordinate> Coordinate_hash;
    size_t operator()(const BusStop& obj) const;
};
}  // namespace std