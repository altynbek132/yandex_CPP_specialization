//
// Created by Addmin on 15.12.2020.
//

#include "entry.h"

std::ostream &operator<<(std::ostream &out, const Entry &entry) {
    out << entry.date << " " << entry.event;
    return out;
}

Entry::Entry(const Date &date, const std::string &event) : date(date), event(event) {}
