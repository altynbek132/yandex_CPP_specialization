//
// Created by Addmin on 13.12.2020.
//

#pragma once

using namespace std;

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

template<typename T>
void RemoveDuplicates(vector<T> &elements);

template<typename T>
void RemoveDuplicates(vector<T> &elements) {
    set<T> s(elements.begin(), elements.end());
    elements = {s.begin(), s.end()};
}
