//
// Created by Addmin on 11.12.2020.
//

#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
    bus_to_stops[bus] = stops;
    for (auto &stop : stops) {
        stop_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
    if (stop_to_buses.count(stop) == 0) {
        return {stop, {}};
    }
    return {stop, stop_to_buses.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
    if (bus_to_stops.count(bus) == 0) {
        return {bus, {}};
    }
    
    vector<pair<string, vector<string>>> stop_with_buses_response;
    for (auto &stop : bus_to_stops.at(bus)) {
        stop_with_buses_response.emplace_back(stop, stop_to_buses.at(stop));
    }
    return {bus, stop_with_buses_response};
}

AllBusesResponse BusManager::GetAllBuses() const {
    return {bus_to_stops};
}
