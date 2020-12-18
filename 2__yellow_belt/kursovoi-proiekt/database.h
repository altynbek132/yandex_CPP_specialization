//
// Created by Addmin on 15.12.2020.
//

#pragma once
#include "date.h"
#include "entry.h"
#include "EventSet.h"
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Database {
 public:
  void Add(const Date &, const string &);
  
  void Print(ostream &) const;
  
  template<class Predicate>
  int RemoveIf(const Predicate &p);
  
  template<class Predicate>
  vector<Entry> FindIf(const Predicate &p) const;
  
  Entry Last(const Date &) const;
 
 private:
  map<Date, EventSet> Date_to_events;
};

void database_test();

template<class Predicate>
int Database::RemoveIf(const Predicate &p) {
    int count = 0;
    for (auto it = Date_to_events.begin(); it != Date_to_events.end();) {
        auto&[date, events] = *it;
        auto &date_ = date;
        const int count_single = events.RemoveIf([&date_, &p](const string &event) {
          return p(date_, event);
        });
        count += count_single;
        if (events.size() == 0) {
            it = Date_to_events.erase(it);
        } else {
            ++it;
        }
    }
    return count;
}


template<class Predicate>
vector<Entry> Database::FindIf(const Predicate &p) const {
    vector<Entry> res;
    for (const auto&[date, events] : Date_to_events) {
        auto &date_ = date;
        auto eventsFound = events.FindIf([&p, & date_](const string &event) {
          return p(date_, event);
        });
        
        for (auto &event : eventsFound) {
            res.emplace_back(date, event);
        }
    }
    return res;
}
