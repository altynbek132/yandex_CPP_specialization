//
// Created by Addmin on 13.12.2020.
//
#ifdef MASLO

#include "solution.h"

#endif

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

//
// Created by Addmin on 13.12.2020.
//


using namespace std;

template<typename T>
void RemoveDuplicates(vector<T> &elements) {
    set<T> s(elements.begin(), elements.end());
    elements = {s.begin(), s.end()};
}
