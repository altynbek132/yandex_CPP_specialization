//
// Created by Addmin on 15.12.2020.
//

#pragma once
#include <unordered_set>
#include <string>
#include <vector>
#include "date.h"
#include "entry.h"
#include <algorithm>

class EventSet {
 public:
  void Add(const std::string &event);
  
  template<class Predicate>
  int RemoveIf(const Predicate &p);
  
  template<class Predicate>
  std::vector<std::string> FindIf(const Predicate &p) const;
  
  const std::string &back() const;
  
  std::size_t size() const;
  
  const std::vector<std::string> &getAll() const;
 
 private:
  std::unordered_set<std::string> events;
  std::vector<std::string> order;
};

// ================================================================

template<class Predicate>
int EventSet::RemoveIf(const Predicate &p) {
    std::unordered_set<std::string> toRemove;
    
    for (auto it = events.begin(); it != events.end();) {
        if (p(*it)) {
            toRemove.insert(*it);
            it = events.erase(it);
        } else {
            it++;
        }
    }
    
    auto it = std::remove_if(order.begin(), order.end(), [&toRemove](const std::string &event) {
      return toRemove.count(event);
    });
    order.erase(it, order.end());
    
    return toRemove.size();
}

template<class Predicate>
std::vector<std::string> EventSet::FindIf(const Predicate &p) const {
    std::vector<std::string> eventsFound;
    for (const auto &event : order) {
        if (p(event)) {
            eventsFound.push_back(event);
        }
    }
    return eventsFound;
}




