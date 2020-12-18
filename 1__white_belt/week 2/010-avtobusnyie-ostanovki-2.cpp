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
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

int main() {
  std::size_t Q;
  cin >> Q;
  map<vector<string>, int> stops_to_bus;
  for (int i = 0; i < Q; ++i) {
    int count;
    cin >> count;
    vector<string> stops;
    for (int i = 0; i < count; ++i) {
      string stop;
      cin >> stop;
      stops.push_back(stop);
    }
    if (stops_to_bus.count(stops)) {
      std::cout << "Already exists for " << stops_to_bus[stops] << std::endl;
    } else {
      int bus_number = stops_to_bus.size() + 1;
      stops_to_bus[stops] = bus_number;
      std::cout << "New bus " << bus_number << std::endl;
    }
  }
  
  return 0;
}





