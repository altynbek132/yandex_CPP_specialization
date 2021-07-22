#pragma once
#include <bits/stdc++.h>
#include "BusStop.h"

using namespace std;

class BusManager {
   public:
    BusManager() = default;
    void AddBusRoute() {}
    void AddBusStop() {}

   private:
    unordered_map<BusStop, size_t> bus_stop_to_count;
};
