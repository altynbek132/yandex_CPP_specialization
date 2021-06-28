#include "BudgetManager.h"
#include "test_runner.h"
#include "utils.h"

using namespace std;

namespace BudgetManager {

Manager::Manager() : income_prefixed_sum_(Date::DiffInDays(begin_, end_), 0) {}
Manager::Manager(const Date::Date& begin, const Date::Date& end)
    : begin_(begin), end_(end), income_prefixed_sum_(Date::DiffInDays(begin_, end_), 0) {}

double Manager::ComputeIncome(Date::Date from, Date::Date to) const {
    CheckYearBoundaries(from), CheckYearBoundaries(to);

    auto from_date_idx = GetIndex(from);
    return income_prefixed_sum_[GetIndex(to)] - (from_date_idx ? income_prefixed_sum_[from_date_idx - 1] : 0);
}
void Manager::Earn(Date::Date from, Date::Date to, double value) {
    CheckYearBoundaries(from), CheckYearBoundaries(to);

    size_t from_idx = GetIndex(from);
    size_t to_idx = GetIndex(to);
    double daily_income = value / (to_idx - from_idx + 1);
    auto end = GetIndex(end_);
    for (auto [i, prev_total_plus] = tuple(from_idx, 0.0);  //
         i < end;                                           //
         ++i) {
        if (i <= to_idx) {
            double& current_pref_income = income_prefixed_sum_[i];
            double new_pref_income = current_pref_income + daily_income + prev_total_plus;
            prev_total_plus = new_pref_income - current_pref_income;
            current_pref_income = new_pref_income;
        } else {
            income_prefixed_sum_[i] += prev_total_plus;
        }
    }
}

void Manager::PayTax(Date::Date from, Date::Date to, double percentage) {
    CheckYearBoundaries(from), CheckYearBoundaries(to);

    double factor = (100 - percentage) / 100.0;
    size_t from_idx = GetIndex(from);
    size_t to_idx = GetIndex(to);
    auto end = GetIndex(end_);
    for (auto [prev_total_minus, i] = tuple(0.0, from_idx);  //
         i < end;                                            //
         ++i)                                                //
    {
        if (i <= to_idx) {
            double income =
                income_prefixed_sum_[i] - (i ? income_prefixed_sum_[i - 1] + prev_total_minus : 0);
            double new_income = income * factor;
            double tax = income - new_income;
            double total_minus = prev_total_minus + tax;
            income_prefixed_sum_[i] -= total_minus;
            prev_total_minus = total_minus;
        } else {
            income_prefixed_sum_[i] -= prev_total_minus;
        }
    }
}

void Manager::CheckYearBoundaries(Date::Date date) const {
#ifndef MASLO
    return;
#endif  // MASLO

    if (CheckBounds(date.getYear(), begin_.getYear(), end_.getYear())) {
        return;
    }
    throw YearOutOfBoundError("chotam?");
}
size_t Manager::GetIndex(Date::Date date) const {
    return Date::DiffInDays(begin_, date);
}

/* ========================================================
BOILERPLATE
======================================================== */

std::ostream& operator<<(std::ostream& os, const std::vector<double>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
ostream& operator<<(ostream& os, const Manager& manager) {
    os << "income_prefixed_sum_: " << manager.income_prefixed_sum_;
    return os;
}

YearOutOfBoundError::YearOutOfBoundError(const std::string& message) : message_(message) {}
const char* YearOutOfBoundError::what() const noexcept {
    return message_.c_str();
}

}  // namespace BudgetManager
