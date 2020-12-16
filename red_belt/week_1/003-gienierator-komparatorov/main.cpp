#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================

struct Date {
  friend bool operator==(const Date &lhs, const Date &rhs) {
      return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
  }
  
  friend ostream &operator<<(ostream &os, const Date &date) {
      os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
      return os;
  }
  
  friend bool operator<(const Date &lhs, const Date &rhs) {
      return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
  }
  
  int year, month, day;
};

struct Time {
  friend bool operator==(const Time &lhs, const Time &rhs) {
      return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
  }
  
  friend bool operator<(const Time &lhs, const Time &rhs) {
      return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
  }
  
  friend ostream &operator<<(ostream &os, const Time &time1) {
      os << "hours: " << time1.hours << " minutes: " << time1.minutes;
      return os;
  }
  
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  uint64_t price;
};


//void SortTickets(vector<AirlineTicket>& tixs) {
//    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
//      return lhs.to < rhs.to;
//    });
//    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
//      return lhs.departure_time < rhs.departure_time;
//    });
//    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
//      return lhs.price < rhs.price;
//    });
//}

#define SORT_BY(method)  \
   [](const AirlineTicket& lhs, const AirlineTicket& rhs) { return lhs.method < rhs.method; }


void SortTickets(vector<AirlineTicket> &tixs) {
    stable_sort(begin(tixs), end(tixs), SORT_BY(to));
    stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
    stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}

#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <ostream>

using namespace std;


void TestSortBy() {
    vector<AirlineTicket> tixs = {
        {"VKO", "AER", "Utair", {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20, 0}, 1200},
        {"AER", "VKO", "Utair", {2018, 3, 5}, {14, 15}, {2018, 3, 5}, {16, 30}, 1700},
        {"AER", "SVO", "Aeroflot", {2018, 3, 5}, {18, 30}, {2018, 3, 5}, {20, 30}, 2300},
        {"PMI", "DME", "Iberia", {2018, 2, 8}, {23, 00}, {2018, 2, 9}, {3, 30}, 9000},
        {"CDG", "SVO", "AirFrance", {2018, 3, 1}, {13, 00}, {2018, 3, 1}, {17, 30}, 8000},
    };
    
    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);
    
    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");
    
    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}



// ==========================================
