//
// Created by Addmin on 02.12.2020.
//

// #include <bits/stdc++.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pi;
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

void printVector(const vector<string> v, string sep) {
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i];
    if (i < v.size() - 1) std::cout << sep;
  }
}
void printVector(const vector<string> v, string sep, string except) {
  for (int i = 0; i < v.size(); ++i) {
    if (except == v[i]) continue;
    std::cout << v[i];
    if (i < v.size() - 1) std::cout << sep;
  }
}

int main() {
//  NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
//  BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
//  STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
//  ALL_BUSES — вывести список всех маршрутов с остановками.
  map<string, vector<string>> bus_to_stop;
  map<string, vector<string>> stop_to_bus;
  
  std::size_t Q;
  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    string operation_code;
    cin >> operation_code;
    if (operation_code == "NEW_BUS") {
      string bus;
      std::size_t stop_count;
      cin >> bus >> stop_count;
      auto &stops = bus_to_stop[bus];
      for (int i = 0; i < stop_count; ++i) {
        string stop;
        cin >> stop;
        stops.push_back(stop);
        stop_to_bus[stop].push_back(bus);
      }
    } else if (operation_code == "BUSES_FOR_STOP") {
      string stop;
      cin >> stop;
      if (!stop_to_bus.count(stop)) {
        std::cout << "No stop" << std::endl;
        continue;
      }
      
      const auto &buses = stop_to_bus[stop];
      if (buses.empty()) {
        std::cout << "No stop";
      } else {
        printVector(buses, " ");
      }
      std::cout << std::endl;
    } else if (operation_code == "STOPS_FOR_BUS") {
      string bus;
      cin >> bus;
      if (!bus_to_stop.count(bus)) {
        std::cout << "No bus" << std::endl;
        continue;
      }
      
      for (const auto &stop: bus_to_stop[bus]) {
        std::cout << "Stop " << stop << ": ";
        const auto &buses = stop_to_bus[stop];
        if (buses.size() == 1) {
          std::cout << "no interchange";
        } else {
          printVector(stop_to_bus[stop], " ", bus);
        }
        std::cout << std::endl;
      }
    } else if (operation_code == "ALL_BUSES") {
      if (bus_to_stop.empty()) {
        std::cout << "No buses";
      } else {
        for (const auto &[bus, stops] : bus_to_stop) {
          std::cout << "Bus " << bus << ": ";
          printVector(stops, " ");
          std::cout << std::endl;
        }
      }
      std::cout << std::endl;
    }
  }
  return 0;
}





