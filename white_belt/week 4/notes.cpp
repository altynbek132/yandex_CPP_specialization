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

struct Day {
  int value;
//  Day (int new_value) {
//    value = new_value;
//  }
};
struct Month {
  int value;
};
struct Year {
  int value;
};

struct Date {
  int year;
  int month;
  int day;
  
  Date(Day new_day, Month new_month, Year new_year) {
    day = new_day.value;
    month = new_month.value;
    year = new_year.value;
  }
};

void PrintDate(const Date &date) {
  std::cout << date.day << "." << date.month << "." << date.year << std::endl;
}

int main() {
  Date date = {Day{1}, Month{1}, Year{2017}};
  Date date2 = {{1}, {1}, {2017}};
  PrintDate(date);
  PrintDate(date2);
  
  return 0;
}
