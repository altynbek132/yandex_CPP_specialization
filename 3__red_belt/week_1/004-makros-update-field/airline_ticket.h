#pragma once

#include <string>

using namespace std;

struct Date {
  int year, month, day;
  
  friend bool operator==(const Date &lhs, const Date &rhs);
  
  friend ostream &operator<<(ostream &os, const Date &date);
  
  friend istream &operator>>(istream &in, Date &date);
  
  friend bool operator<(const Date &lhs, const Date &rhs);
};



struct Time {
  int hours, minutes;
  
  friend bool operator==(const Time &lhs, const Time &rhs);
  
  friend bool operator<(const Time &lhs, const Time &rhs);
  
  friend istream &operator>>(istream &in, Time &time);
  
  friend ostream &operator<<(ostream &os, const Time &time1);
};




struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};
