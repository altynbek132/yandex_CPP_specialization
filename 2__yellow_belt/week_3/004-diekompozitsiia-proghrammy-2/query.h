//
// Created by Addmin on 11.12.2020.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};


istream &operator>>(istream &is, QueryType &qt);

istream &operator>>(istream &is, Query &q);
