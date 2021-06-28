#include "BudgetManager.h"
#include "test_runner.h"
#include "utils.h"

using namespace std;

namespace BudgetManager {

Manager::Manager() : prefix_sum_(Date::DiffInDays(begin_, end_)) {}
Manager::Manager(const Date::Date& begin, const Date::Date& end)
    : begin_(begin), end_(end), prefix_sum_(Date::DiffInDays(begin_, end_)) {}

double Manager::ComputeIncome(Date::Date from, Date::Date to) const {
    CheckYearBoundaries(from), CheckYearBoundaries(to);

    auto from_date_idx = GetIndex(from);
    auto income =
        prefix_sum_[GetIndex(to)].income - (from_date_idx ? prefix_sum_[from_date_idx - 1].income : 0);
    auto spending =
        prefix_sum_[GetIndex(to)].spending - (from_date_idx ? prefix_sum_[from_date_idx - 1].spending : 0);
    return income - spending;
}

void Manager::Earn(Date::Date from, Date::Date to, double value) {
    CheckYearBoundaries(from), CheckYearBoundaries(to);

    size_t from_idx = GetIndex(from);
    size_t to_idx = GetIndex(to);
    double daily_income = value / (to_idx - from_idx + 1);
    IncreasePrefixedSumEntries(from_idx, to_idx, daily_income,
                               [](Entry& entry) { return ref(entry.income); });
}

void Manager::Spend(Date::Date from, Date::Date to, double value) {
    CheckYearBoundaries(from), CheckYearBoundaries(to);

    size_t from_idx = GetIndex(from);
    size_t to_idx = GetIndex(to);
    double daily_spending = value / (to_idx - from_idx + 1);
    IncreasePrefixedSumEntries(from_idx, to_idx, daily_spending,
                               [](Entry& entry) { return ref(entry.spending); });
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
            double income = prefix_sum_[i].income - (i ? prefix_sum_[i - 1].income + prev_total_minus : 0);
            double new_income = income * factor;
            double tax = income - new_income;
            double total_minus = prev_total_minus + tax;
            prefix_sum_[i].income -= total_minus;
            prev_total_minus = total_minus;
        } else {
            prefix_sum_[i].income -= prev_total_minus;
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
    throw YearOutOfBoundError("YearOutOfBoundError");
}
size_t Manager::GetIndex(Date::Date date) const {
    return Date::DiffInDays(begin_, date);
}

/* ========================================================
BOILERPLATE
======================================================== */

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& s) {
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
    os << manager.prefix_sum_;
    return os;
}

ostream& operator<<(ostream& os, const Manager::Entry& entry) {
    os << "{" << entry.income << ", " << entry.spending << "}";
    return os;
}

YearOutOfBoundError::YearOutOfBoundError(const std::string& message) : message_(message) {}
const char* YearOutOfBoundError::what() const noexcept {
    return message_.c_str();
}

}  // namespace BudgetManager
