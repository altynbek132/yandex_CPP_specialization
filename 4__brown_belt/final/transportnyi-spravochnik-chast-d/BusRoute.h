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
    mutable std::optional<size_t> unique_stops_count;
    mutable std::optional<double> curvature;

    friend std::ostream& operator<<(std::ostream& os, const BusRoute& route);
    size_t getStopsCount() const;
};

std::ostream& operator<<(std::ostream& out, const BusRoute::Type& type);
