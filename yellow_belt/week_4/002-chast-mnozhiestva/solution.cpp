//
// Created by Addmin on 13.12.2020.
//
#ifdef MASLO

#include "solution.h"

#endif

#include <vector>
#include <algorithm>
#include <iostream>
//
// Created by Addmin on 13.12.2020.
//

//#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;


template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border);

template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
    vector<T> res;
    copy_if(elements.begin(), elements.end(), back_inserter(res), [border](T val) { return val > border; });
    return res;
}
