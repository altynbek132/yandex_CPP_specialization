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

map<char, int> build(const string &str) {
    map<char, int> m;
    for (auto &ch : str) {
        m[ch]++;
    }
    return m;
}

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string first, second;
        cin >> first >> second;
        if (build(first) == build(second)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
        
    }
    return 0;
}





