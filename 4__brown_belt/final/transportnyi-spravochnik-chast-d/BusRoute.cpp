#include "BusRoute.h"
#include <bits/stdc++.h>

#include "output_reload.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const BusRoute& route) {
    os << "bus_name: " << route.bus_name << " stop_names: " << route.stop_names << " type: " << route.type
       << " route_length: " << route.route_length.value_or(0);
    return os;
}
size_t BusRoute::getStopsCount() const {
    switch (type) {
        case BusRoute::Type::STRAIGHT: {
            return stop_names.size() * 2 - 1;
        }
        case BusRoute::Type::LOOPED: {
            return stop_names.size() + 1;
        }
        default:
            throw runtime_error("chotam?");
    }

    return 0;
}
std::ostream& operator<<(ostream& out, const BusRoute::Type& type) {
    switch (type) {
        case BusRoute::Type::LOOPED: {
            out << "LOOPED";
            break;
        }
        case BusRoute::Type::STRAIGHT: {
            out << "STRAIGHT";
            break;
        }
        default:
            throw runtime_error("chotam?");
    }
    return out;
}
