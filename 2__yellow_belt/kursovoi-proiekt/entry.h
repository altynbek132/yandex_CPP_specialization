//
// Created by Addmin on 15.12.2020.
//

#pragma once
#include "date.h"
#include <string>
#include <iostream>

struct Entry {
  Entry(const Date &date, const std::string &event);
  Date date;
  std::string event;
};

std::ostream &operator<<(std::ostream &out, const Entry &entry);
