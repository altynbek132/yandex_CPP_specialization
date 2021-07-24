#pragma once
#include <bits/stdc++.h>

struct BusRoute {
    enum class Type {
        LOOPED,
        STRAIGHT,
    };

    std::string bus_name;
    std::vector<std::string> stop_names;
    Type type;

    mutable std::optional<double> route_length;
};
