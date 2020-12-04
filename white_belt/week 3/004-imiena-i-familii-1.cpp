//
// Created by Addmin on 03.12.2020.
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


class Person {
 public:
  void ChangeFirstName(int year, const string &first_name) {
    // добавить факт изменения имени на first_name в год year
    _year_to_first_name[year] = first_name;
  }
  void ChangeLastName(int year, const string &last_name) {
    // добавить факт изменения фамилии на last_name в год year
    _year_to_last_name[year] = last_name;
  }
  string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
    string first = find_closest(year, _year_to_first_name);
    string last = find_closest(year, _year_to_last_name);
    if (first.empty() && last.empty()) {
      return "Incognito";
    }
    if (first.empty()) {
      return last + " with unknown first name";
    }
    if (last.empty()) {
      return first + " with unknown last name";
    }
    return first + " " + last;
  }
 private:
  // приватные поля
  map<int, string> _year_to_first_name;
  map<int, string> _year_to_last_name;
  
  string find_closest(int year_, const map<int, string> &m_) {
    string closest;
    for (auto &[year, value] : m_) {
      if (year > year_) break;
      closest = value;
    }
    return closest;
  }
};
int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
