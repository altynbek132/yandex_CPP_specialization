#include "Date.h"
#pragma once
#include <bits/stdc++.h>
#include <ostream>

namespace BudgetManager {

class Manager {
   public:
    struct Entry {
        double income = 0;
        double spending = 0;
        friend std::ostream& operator<<(std::ostream& os, const Entry& entry);
    };

   public:
    Manager();
    Manager(const Date::Date& begin, const Date::Date& end);
    double ComputeIncome(Date::Date from, Date::Date to) const;
    void Earn(Date::Date from, Date::Date to, double value);
    void Spend(Date::Date from, Date::Date to, double value);
    void PayTax(Date::Date from, Date::Date to, double percentage = 13);
    friend std::ostream& operator<<(std::ostream& os, const Manager& manager);

   private:
    template <typename Func>
    void IncreasePrefixedSumEntries(size_t from_idx, size_t to_idx, double single, Func GetSpecific) {
        auto end = GetIndex(end_);
        for (auto [i, prev_total_plus] = std::tuple(from_idx, 0.0);  //
             i < end;                                                //
             ++i) {
            if (i <= to_idx) {
                double& current_pref_income = GetSpecific(prefix_sum_[i]);
                double new_pref_income = current_pref_income + single + prev_total_plus;
                prev_total_plus = new_pref_income - current_pref_income;
                current_pref_income = new_pref_income;
            } else {
                GetSpecific(prefix_sum_[i]) += prev_total_plus;
            }
        }
    }
    Date::Date begin_{2000, 1, 1};

#ifdef MASLO
    Date::Date end_{2002, 1, 2};
#endif  // MASLO

#ifndef MASLO
    Date::Date end_{2100, 1, 1};
#endif  // MASLO

    std::vector<Entry> prefix_sum_;

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
