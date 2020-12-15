//
// Created by Addmin on 15.12.2020.
//

#include "date.h"
//#include "utilities.h"
#include <sstream>
#include <tuple>
#include <iomanip>

Date ParseDate(std::istream &in) {
    int year, month, day;
    in >> std::ws;
    in >> year;
    in.ignore(1);
    in >> month;
    in.ignore(1);
    in >> day;
    return Date(year, month, day);
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << std::setfill('0')
       << std::setw(4) << date.GetYear()
       << '-' << std::setw(2) << date.GetMonth()
       << '-' << std::setw(2) << date.GetDay();
    return os;
}


Date::Date(int year, int month, int day) : year(year), month(month), day(day) {
    if (month < 1 || month > 12) {
        std::stringstream error;
        error << "Month value is invalid: " << month;
        throw std::logic_error(error.str());
    }
    if (day < 1 || day > 31) {
        std::stringstream error;
        error << "Day value is invalid: " << day;
        throw std::logic_error(error.str());
    }
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

bool Date::operator==(const Date &rhs) const {
    return std::tie(year, month, day) == std::tie(rhs.year, rhs.month, rhs.day);
}

bool Date::operator!=(const Date &rhs) const {
    return !(rhs == *this);
}

bool Date::operator<(const Date &rhs) const {
    return std::tie(year, month, day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool Date::operator<=(const Date &rhs) const {
    return std::tie(year, month, day) <= std::tie(rhs.year, rhs.month, rhs.day);
}

bool Date::operator>(const Date &rhs) const {
    return std::tie(year, month, day) > std::tie(rhs.year, rhs.month, rhs.day);
}

bool Date::operator>=(const Date &rhs) const {
    return std::tie(year, month, day) >= std::tie(rhs.year, rhs.month, rhs.day);
}
