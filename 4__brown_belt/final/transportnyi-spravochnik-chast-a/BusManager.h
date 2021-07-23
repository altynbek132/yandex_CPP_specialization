#pragma once
#include <bits/stdc++.h>
#include "BusRoute.h"
#include "BusStop.h"
#include "Request.h"

using namespace std;

/*
 fields:
 stop_name to coord
 stop_name to count

 methods:
 AddBusRoute O(1)
 AddBusStop O(1)
 ReadBusRouteInfoResultType
    count of stops O(1)
    count of unique stops for route (can be cached but we have to use bus_name_to_bus_routes map) O(n)
    route length (cache) O(1?)
 * */

class BusManager {
   public:
    BusManager() = default;
    void AddBusRoute(BusRoute bus_route);
    void AddBusStop(BusStop bus_stop);
    Request::ReadBusRouteInfoResultType ReadBusRouteInfo(string bus_name);

   private:
    unordered_map<string, Coordinate> bus_stop_name_to_coordinate;
    unordered_map<string, size_t> bus_stop_name_to_count;
    unordered_map<string, BusRoute> bus_name_to_bus_route;
};
