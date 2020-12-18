//
// Created by Addmin on 15.12.2020.
//

#include "EventSet.h"

void EventSet::Add(const std::string &event) {
    if (events.count(event) == 0) {
        events.insert(event);
        order.push_back(event);
    }
}

const std::string & EventSet::back() const {
    return order.back();
}

std::size_t EventSet::size() const {
    return events.size();
}

const std::vector<std::string> &EventSet::getAll() const {
    return order;
}
