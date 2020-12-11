//
// Created by Addmin on 11.12.2020.
//

#include "responses.h"


ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        os << Join(r.buses, ' ');
    }
    return os;
}


ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (r.stop_with_buses.empty()) {
        std::cout << "No bus";
        return os;
    }
    
    bool first = true;
    for (const auto &[stop, buses] : r.stop_with_buses) {
        if (!first) {
            os << endl;
        }
        first = false;
        
        os << "Stop " << stop << ": ";
        if (buses.size() == 1 && buses[0] == r.bus) {
            os << "no interchange";
            continue;
        }
        
        bool first_ = true;
        for (const auto &bus : buses) {
            if (bus == r.bus) {
                continue;
            }
            if (!first_) {
                os << ' ';
            }
            first_ = false;
            os << bus;
        }
    }
    return os;
}


ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (r.bus_to_stops.empty()) {
        os << "No buses";
        return os;
    }
    bool first = true;
    for (auto &[bus, stops] : r.bus_to_stops) {
        if (!first) {
            os << endl;
        }
        first = false;
        os << "Bus " << bus << ": " << Join(stops, ' ');
    }
    return os;
}
