#include <tuple>
#pragma once

#include <ostream>
#include <string>
using namespace std;

struct Date {
    friend ostream& operator<<(ostream& os, const Date& date);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    int year, month, day;
};


struct Time {
    friend ostream& operator<<(ostream& os, const Time& time1);
    friend bool operator<(const Time& lhs, const Time& rhs);
    friend bool operator>(const Time& lhs, const Time& rhs);
    friend bool operator<=(const Time& lhs, const Time& rhs);
    friend bool operator>=(const Time& lhs, const Time& rhs);
    friend bool operator==(const Time& lhs, const Time& rhs);
    friend bool operator!=(const Time& lhs, const Time& rhs);
    int hours, minutes;
};

struct AirlineTicket {
    friend ostream& operator<<(ostream& os, const AirlineTicket& ticket);
    friend bool operator<(const AirlineTicket& lhs, const AirlineTicket& rhs);
    friend bool operator>(const AirlineTicket& lhs, const AirlineTicket& rhs);
    friend bool operator<=(const AirlineTicket& lhs, const AirlineTicket& rhs);
    friend bool operator>=(const AirlineTicket& lhs, const AirlineTicket& rhs);
    string from;
    string to;
    string airline;
    Date departure_date;
    Time departure_time;
    Date arrival_date;
    Time arrival_time;
    int price;
};
