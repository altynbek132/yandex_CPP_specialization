#include <bits/stdc++.h>

#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

// airline_ticket.h operators reload
bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}
bool operator!=(const Date& lhs, const Date& rhs) {
    return !(rhs == lhs);
}
bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}
bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}
bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}
ostream& operator<<(ostream& os, const Date& date) {
    os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
    return os;
}
bool operator==(const Time& lhs, const Time& rhs) {
    return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}
bool operator!=(const Time& lhs, const Time& rhs) {
    return !(rhs == lhs);
}
bool operator<(const Time& lhs, const Time& rhs) {
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}
bool operator>(const Time& lhs, const Time& rhs) {
    return rhs < lhs;
}
bool operator<=(const Time& lhs, const Time& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const Time& lhs, const Time& rhs) {
    return !(lhs < rhs);
}
ostream& operator<<(ostream& os, const Time& time1) {
    os << "hours: " << time1.hours << " minutes: " << time1.minutes;
    return os;
}

bool operator<(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return std::tie(lhs.from, lhs.to, lhs.airline, lhs.departure_date, lhs.departure_time, lhs.arrival_date,
                    lhs.arrival_time, lhs.price) < std::tie(rhs.from, rhs.to, rhs.airline, rhs.departure_date,
                                                            rhs.departure_time, rhs.arrival_date,
                                                            rhs.arrival_time, rhs.price);
}
bool operator>(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return rhs < lhs;
}
bool operator<=(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return !(lhs < rhs);
}
ostream& operator<<(ostream& os, const AirlineTicket& ticket) {
    os << "from: " << ticket.from << " to: " << ticket.to << " airline: " << ticket.airline
       << " departure_date: " << ticket.departure_date << " departure_time: " << ticket.departure_time
       << " arrival_date: " << ticket.arrival_date << " arrival_time: " << ticket.arrival_time
       << " price: " << ticket.price;
    return os;
}

// END reload

istream& operator>>(istream& in, Date& date) {
    in >> date.year;
    in.ignore(1);
    in >> date.month;
    in.ignore(1);
    in >> date.day;
    return in;
}

istream& operator>>(istream& in, Time& time) {
    in >> time.hours;
    in.ignore(1);
    in >> time.minutes;
    return in;
}

#define UPDATE_FIELD(ticket, field, values) \
    {                                       \
        auto it = values.find(#field);      \
        if (it != values.end()) {           \
            istringstream is(it->second);   \
            is >> ticket.field;             \
        }                                   \
    }

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
