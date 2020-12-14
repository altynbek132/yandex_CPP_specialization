//
// Created by Addmin on 13.12.2020.
//
#ifdef MASLO

#include "solution.h"

#endif

#include <vector>
#include <algorithm>
#include <iostream>


void PrintVectorPart(const std::vector<int> &numbers) {
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int val) { return val < 0; });
    auto begin = numbers.begin();
    while (begin != it) {
        std::cout << *--it << " ";
    }
}
