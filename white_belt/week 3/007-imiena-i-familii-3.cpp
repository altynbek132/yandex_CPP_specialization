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
  Person(const string &first, const string &last, const int &year) : birth_year(year) {
    ChangeFirstName(year, first);
    ChangeLastName(year, last);
  }
  void ChangeFirstName(int year, const string &first_name) {
    if (year < birth_year) {
      return;
    }
    _year_to_first_name[year] = first_name;
  }
  void ChangeLastName(int year, const string &last_name) {
    if (year < birth_year) {
      return;
    }
    _year_to_last_name[year] = last_name;
  }
  string GetFullName(int year) const {
    vs firsts = get_history(year, _year_to_first_name);
    vs lasts = get_history(year, _year_to_last_name);
    string first = firsts.empty() ? "" : firsts.back();
    string last = lasts.empty() ? "" : lasts.back();
    return build_get_name_response(first, last);
  }
  string GetFullNameWithHistory(int year) const {
    vs firsts = get_history(year, _year_to_first_name);
    vs lasts = get_history(year, _year_to_last_name);
    string first = build_names(firsts);
    string last = build_names(lasts);
    return build_get_name_response(first, last);
  }
 
 private:
  map<int, string> _year_to_first_name;
  map<int, string> _year_to_last_name;
  int birth_year;
  
  static vector<string> get_history(int year_, const map<int, string> &m_) {
    vs history;
    for (auto &[year, value] : m_) {
      if (year > year_) break;
      if (history.empty() || history.back() != value) {
        history.push_back(value);
      }
    }
    return history;
  }
  
  static string build_names(const vs &names) {
    if (names.empty()) {
      return "";
    }
    string name = names.back();
    
    for (size_t i = names.size() - 1; i-- > 0;) {
      if (i == names.size() - 2) {
        name += " (";
      }
      name += names[i];
      if (i == 0) {
        name += ")";
      } else {
        name += ", ";
      }
    }
    return name;
  }
  
  static string build_get_name_response(const string &first, const string &last) {
    if (first.empty() && last.empty()) {
      return "No person";
    }
    if (first.empty()) {
      return last + " with unknown first name";
    }
    if (last.empty()) {
      return first + " with unknown last name";
    }
    return first + " " + last;
  }
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeFirstName(1959, "Maslo");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967, 1959}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  for (int year : {1965, 1967, 1959}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
