#include "BusRoute.h"
#include <bits/stdc++.h>

#ifdef MASLO
#include "test_runner.h"
#endif  // MASLO

using namespace std;

std::ostream& operator<<(std::ostream& os, const BusRoute& route) {
#ifdef MASLO

    os << "bus_name: " << route.bus_name << " stop_names: " << route.stop_names << " type: " << route.type
       << " route_length: " << route.route_length.value_or(0);
#endif  // MASLO

    return os;
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
