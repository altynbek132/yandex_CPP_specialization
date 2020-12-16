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


#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

bool operator==(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

ostream &operator<<(ostream &os, const Date &date) {
    os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
    return os;
}

istream &operator>>(istream &in, Date &date) {
    in >> date.year;
    in.ignore(1);
    in >> date.month;
    in.ignore(1);
    in >> date.day;
    return in;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Time &lhs, const Time &rhs) {
    return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}

bool operator<(const Time &lhs, const Time &rhs) {
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}

istream &operator>>(istream &in, Time &time) {
    in >> time.hours;
    in.ignore(1);
    in >> time.minutes;
    return in;
}

ostream &operator<<(ostream &os, const Time &time1) {
    os << "hours: " << time1.hours << " minutes: " << time1.minutes;
    return os;
}

#define UPDATE_FIELD(ticket, field, values)         \
    {                                               \
        auto it = values.find(#field);                      \
        if (it != values.end()) {                           \
            istringstream is(it->second);                       \
            is >> ticket.field;                                 \
        }                                                   \
    }                                                   \
\
// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;
    
    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);
    
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);
    
    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);
    
    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}


// ==========================================
