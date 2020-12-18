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
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

string join(const vs &v, const string &sep) {
  string str;
  for (size_t i = 0; i < v.size(); ++i) {
    str += v[i];
    if (i < v.size() - 1) {
      str += sep;
    }
  }
  return str;
}

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
  string GetFullNameWithHistory(int year) {
    // получить все имена и фамилии по состоянию на конец года year
    vs firsts = get_history(year, _year_to_first_name);
    vs lasts = get_history(year, _year_to_last_name);
    if (firsts.empty() && lasts.empty()) {
      return "Incognito";
    }
    string lasts_history = gen_history_names(lasts);
    string firsts_history = gen_history_names(firsts);
    if (firsts.empty()) {
      return lasts_history + " with unknown first name";
    }
    if (lasts.empty()) {
      return firsts_history + " with unknown last name";
    }
    return firsts_history + " " + lasts_history;
  }
 private:
  // приватные поля
  map<int, string> _year_to_first_name;
  map<int, string> _year_to_last_name;
  
  static string gen_history_names(const vs &v) {
    if (v.empty()) {
      return "";
    }
    string str;
    str += v.front();
    if (v.size() > 1) {
      str += " (" + join({v.begin() + 1, v.end()}, ", ") + ")";
    }
    return str;
  }
  
  static string find_closest(int year_, const map<int, string> &m_) {
    string closest;
    for (auto &[year, value] : m_) {
      if (year > year_) break;
      closest = value;
    }
    return closest;
  }

//  get reversed history of names
  static vector<string> get_history(int year_, const map<int, string> &m_) {
    vs history;
    for (auto &[year, value] : m_) {
      if (year > year_) break;
      if (history.empty() || history.back() != value) {
        history.push_back(value);
      }
    }
    reverse(history.begin(), history.end());
    return history;
  }
  
};

void test1() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
}

void test2() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");
  
  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");
  
  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
}

int main() {
  test2();
  
  return 0;
}
