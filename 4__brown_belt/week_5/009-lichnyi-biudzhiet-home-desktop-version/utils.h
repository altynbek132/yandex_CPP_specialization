#pragma once
#include <istream>

bool CheckAndSkip(std::istream& is, char ch);

bool CheckBounds(int val, int lower, int upper);
