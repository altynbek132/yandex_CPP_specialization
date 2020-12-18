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


using namespace std;

vector<string> SplitIntoWords(const string &s) {
    vector<string> res;
    for (auto it = s.begin();;) {
        auto end = find(it, s.end(), ' ');
        res.emplace_back(it, end);
        if (end == s.end()) { break; }
        it = ++end;
    }
    return res;
}
