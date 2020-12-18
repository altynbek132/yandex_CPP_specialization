//
// Created by Addmin on 11.12.2020.
//

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.h"


using namespace std;
struct BusesForStopResponse {
  string stop;
  vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stop_with_buses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse {
  map<string, vector<string>> bus_to_stops;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);
