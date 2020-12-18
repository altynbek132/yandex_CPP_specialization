//
// Created by Addmin on 15.12.2020.
//

#include "database.h"
#include <algorithm>
#include <iterator>
#include <sstream>

void Database::Add(const Date &date, const string &event) {
    auto &events = Date_to_events[date];
    events.Add(event);
}

void Database::Print(ostream &out) const {
    for (const auto&[date, events] : Date_to_events) {
        for (const auto &event : events.getAll()) {
            out << date << " " << event << std::endl;
        }
    }
}

Entry Database::Last(const Date &date_) const {
    auto it = Date_to_events.upper_bound(date_);
    if (it == Date_to_events.begin()) {
        stringstream error;
        error << "no events before given date: " << date_;
        throw std::invalid_argument(error.str());
    }
    const auto &[date, events] = *--it;
    std::stringstream ss;
    return {date, events.back()};
}
