//
// Created by Addmin on 15.12.2020.
//

#pragma once
#include <exception>

enum Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

template<class T>
bool PerformComparison(const Comparison &cmp, const T &lhs, const T &rhs) {
    switch (cmp) {
        case Comparison::Less: {
            return lhs < rhs;
        }
        case Comparison::LessOrEqual: {
            return lhs <= rhs;
        }
        case Comparison::Greater: {
            return lhs > rhs;
        }
        case Comparison::GreaterOrEqual: {
            return lhs >= rhs;
        }
        case Comparison::Equal: {
            return lhs == rhs;
        }
        case Comparison::NotEqual: {
            return lhs != rhs;
        }
        default: {
            throw std::logic_error("unknown logical operation!");
        }
    }
}
