//
// Created by Addmin on 02.12.2020.
//

// #include <bits/stdc++.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pi;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

void Reverse (vector<int>& v) {
    vector<int> vv;
    for (size_t i = v.size(); i --> 0 ;) {
        vv.push_back(v[i]);
    }
    v.clear();
    swap(v,vv);

}

int main() {
    vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);
// numbers должен оказаться равен {2, 4, 3, 5, 1}
    return 0;
}
