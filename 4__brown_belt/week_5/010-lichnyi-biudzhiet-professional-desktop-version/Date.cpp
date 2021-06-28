#include "Date.h"
#include <tuple>
#include <utility>
#include "utils.h"

using namespace std;

namespace Date {
istream& operator>>(istream& is, Date& date) {
    char delim = '-';
    bool success =                  //
        is >> date.year_            //
        && CheckAndSkip(is, delim)  //

        && is >> date.month_                //
        && CheckBounds(date.month_, 1, 13)  //
        && CheckAndSkip(is, delim)          //

        && is >> date.day_                 //
        && CheckBounds(date.day_, 1, 32);  //

    if (!success) {
        throw ParseError("incorrect date format");
    }

    return is;
}

time_t Date::AsTimestamp() const {
    std::tm t;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_mday = day_;
    t.tm_mon = month_ - 1;
    t.tm_year = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
}

// including "from", excluding "to"
size_t DiffInDays(const Date& from, const Date& to) {
    const time_t timestamp_from = from.AsTimestamp();
    const time_t timestamp_to = to.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    auto res = (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
    return res;
}

/* ========================================================
BOILERPLATE
======================================================== */

ostream& operator<<(ostream& os, const Date& date) {
    os << date.year_ << '-' << date.month_ << '-' << date.day_;
    return os;
}
int Date::getYear() const {
    return year_;
}
void Date::setYear(int year) {
    Date::year_ = year;
}
int Date::getMonth() const {
    return month_;
}
void Date::setMonth(int month) {
    Date::month_ = month;
}
int Date::getDay() const {
    return day_;
}
void Date::setDay(int day) {
    Date::day_ = day;
}
bool Date::operator==(const Date& rhs) const {
    return tie(year_, month_, day_) == tie(rhs.year_, rhs.month_, rhs.day_);
}
bool Date::operator!=(const Date& rhs) const {
    return !(rhs == *this);
}
Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
Date::Date() {}

ParseError::ParseError(std::string message) : message_(std::move(message)) {}
const char* ParseError::what() const noexcept {
    return message_.c_str();
}

}  // namespace Date
