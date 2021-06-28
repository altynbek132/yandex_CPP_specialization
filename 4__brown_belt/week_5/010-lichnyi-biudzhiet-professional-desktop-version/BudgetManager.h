#include "Date.h"
#pragma once
#include <bits/stdc++.h>
#include <ostream>

namespace BudgetManager {

class Manager {
   public:
    Manager();
    Manager(const Date::Date& begin, const Date::Date& end);
    double ComputeIncome(Date::Date from, Date::Date to) const;
    void Earn(Date::Date from, Date::Date to, double value);
    void PayTax(Date::Date from, Date::Date to, double percentage = 13);
    friend std::ostream& operator<<(std::ostream& os, const Manager& manager);

   private:
    Date::Date begin_{2000, 1, 1};

#ifdef MASLO
    Date::Date end_{2002, 1, 2};
#endif  // MASLO

#ifndef MASLO
    Date::Date end_{2100, 1, 1};
#endif  // MASLO

    std::vector<double> income_prefixed_sum_;

    void CheckYearBoundaries(Date::Date date) const;
    size_t GetIndex(Date::Date date) const;
};

class YearOutOfBoundError : public std::exception {
   private:
    std::string message_;

   public:
    explicit YearOutOfBoundError(const std::string& message);
    const char* what() const noexcept override;
};

}  // namespace BudgetManager
