#pragma once
#include <bits/stdc++.h>
#include "BusRoute.h"
#include "BusStop.h"
#include "Response.h"

/*
 fields:
 stop_name to coord
 stop_name to count

 methods:
 AddBusRoute O(1)
 AddBusStop O(1)
 ReadBusRouteInfo
    count of stops O(1)
    count of unique stops for route (can be cached but we have to use bus_name_to_bus_routes map) O(n)
    route length (cache) O(1?)
 * */

class BusManager {
   public:
    BusManager() = default;
    void AddBusRoute(BusRoute bus_route);
    void AddBusStop(BusStop bus_stop);
    Response::Holder ReadBusRouteInfo(std::string_view bus_name) const;

   private:
    std::unordered_map<std::string, BusRoute> bus_name_to_bus_route;

    // todo: use string_view
    std::unordered_map<std::string, Coordinate> bus_stop_name_to_coordinate;
    std::unordered_map<std::string, size_t> bus_stop_name_to_count;
};
