#pragma once
#include <bits/stdc++.h>
#include <ostream>

struct DistanceToNeighborStop {
    double distance;
    std::string stop_name;

    friend std::ostream& operator<<(std::ostream& os, const DistanceToNeighborStop& stop);
};
