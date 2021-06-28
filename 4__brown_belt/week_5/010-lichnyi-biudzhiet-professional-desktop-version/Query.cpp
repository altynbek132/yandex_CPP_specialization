#include "Query.h"
#include <iostream>
#include <string>

using namespace std;

namespace Query {
Query::Query(const Date::Date& from, const Date::Date& to) : from(from), to(to) {}
Query::Query(const Date::Date& from, const Date::Date& to, double value) : from(from), to(to), value(value) {}

shared_ptr<Query> Read(istream& is) {
    string name;
    cin >> name;
    Date::Date from, to;
    is >> from >> to;

    if (name == "ComputeIncome") {
        return make_shared<ComputeIncome>(from, to);
    }
    if (name == "Earn") {
        double value;
        is >> value;
        return make_shared<Earn>(from, to, value);
    }
    if (name == "Spend") {
        double value;
        is >> value;
        return make_shared<Spend>(from, to, value);
    }
    if (name == "PayTax") {
        double percentage;
        is >> percentage;
        return make_shared<PayTax>(from, to, percentage);
    }
    throw UnknownQueryError("UnknownQueryError");
}

/* ========================================================
BOILERPLATE
======================================================== */

UnknownQueryError::UnknownQueryError(std::string message) : message_(std::move(message)) {}
const char* UnknownQueryError::what() const noexcept {
    return message_.c_str();
}

}  // namespace Query
