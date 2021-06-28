#pragma once
#include <ctime>
#include <exception>
#include <sstream>

namespace Date {

class ParseError : public std::exception {
   private:
    std::string message_;

   public:
    explicit ParseError(std::string message);
    const char* what() const noexcept override;
};

class Date {
   private:
    int year_ = 1970;
    int month_ = 1;
    int day_ = 1;

   public:
    Date();
    Date(int year, int month, int day);

    friend std::istream& operator>>(std::istream& os, Date& date);
    time_t AsTimestamp() const;

    /* ========================================================
    BOILERPLATE
    ======================================================== */

   public:
    bool operator==(const Date& rhs) const;
    bool operator!=(const Date& rhs) const;
    int getYear() const;
    void setYear(int year);
    int getMonth() const;
    void setMonth(int month);
    int getDay() const;
    void setDay(int day);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

size_t DiffInDays(const Date& from, const Date& to);

}  // namespace Date