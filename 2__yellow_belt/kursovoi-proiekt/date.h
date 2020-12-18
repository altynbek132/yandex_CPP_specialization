//
// Created by Addmin on 15.12.2020.
//

#pragma once
#include <iostream>

class Date {
 public:
  Date(int year, int month, int day);
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
  bool operator==(const Date &rhs) const;
  bool operator!=(const Date &rhs) const;
  bool operator<(const Date &rhs) const;
  bool operator<=(const Date &rhs) const;
  bool operator>(const Date &rhs) const;
  bool operator>=(const Date &rhs) const;
 private:
  int year, month, day;
};

Date ParseDate(std::istream &in);

std::ostream &operator<<(std::ostream &, const Date &);
