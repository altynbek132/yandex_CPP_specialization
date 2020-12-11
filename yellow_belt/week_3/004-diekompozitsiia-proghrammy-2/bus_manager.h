//
// Created by Addmin on 11.12.2020.
//

#pragma once

#include "responses.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class BusManager {
 public:
  void AddBus(const string &bus, const vector<string> &stops);
  
  BusesForStopResponse GetBusesForStop(const string &stop) const;
  
  StopsForBusResponse GetStopsForBus(const string &bus) const;
  
  AllBusesResponse GetAllBuses() const;
 
 private:
  map<string, vector<string>> bus_to_stops;
  map<string, vector<string>> stop_to_buses;
};
