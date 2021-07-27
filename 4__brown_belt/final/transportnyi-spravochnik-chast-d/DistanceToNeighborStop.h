#pragma once
#include <bits/stdc++.h>
#include <ostream>

struct DistanceToNeighborStop {
    int distance;
    std::string stop_name;

    friend std::ostream& operator<<(std::ostream& os, const DistanceToNeighborStop& stop);
};
