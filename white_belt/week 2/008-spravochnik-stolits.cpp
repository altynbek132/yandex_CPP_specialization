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

int main() {
  std::size_t Q;
  cin >> Q;
  map<string, string> country_to_capital;
  for (int i = 0; i < Q; ++i) {
    string operation;
    cin >> operation;
    if (operation == "CHANGE_CAPITAL") {
      string country, new_capital;
      cin >> country >> new_capital;
      if (country_to_capital.count(country)) {
        auto &capital = country_to_capital[country];
        auto old_capital = capital;

        if (old_capital == new_capital) {
          std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
        } else {
          capital = new_capital;
          std::cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital
                    << std::endl;
        }
      } else {
        country_to_capital[country] = new_capital;
        std::cout << "Introduce new country " << country << " with capital " << new_capital << std::endl;
      }
    } else if (operation == "RENAME") {
      string old_country_name, new_country_name;
      cin >> old_country_name >> new_country_name;

      if (old_country_name == new_country_name) {
        std::cout << "Incorrect rename, skip" << std::endl;
      } else if (country_to_capital.count(new_country_name) || !country_to_capital.count(old_country_name)) {
        std::cout << "Incorrect rename, skip" << std::endl;
      } else {
        swap(country_to_capital[new_country_name], country_to_capital[old_country_name]);
        country_to_capital.erase(old_country_name);
        std::cout << "Country " << old_country_name << " with capital " << country_to_capital[new_country_name]
                  << " has been renamed to " << new_country_name << std::endl;
      }
    } else if (operation == "ABOUT") {
      string country;
      cin >> country;

      if (country_to_capital.count(country)) {
        std::cout << "Country " << country << " has capital " << country_to_capital[country] << std::endl;
      } else {
        std::cout << "Country " << country << " doesn't exist" << std::endl;
      }
    } else if (operation == "DUMP") {
      if (country_to_capital.empty()) {
        std::cout << "There are no countries in the world" << std::endl;
      } else {
        for (auto &[country, capital] : country_to_capital) {
          std::cout << country << '/' << capital << ' ';
        }
        std::cout << std::endl;
      }
    }
  }
  return 0;
}
