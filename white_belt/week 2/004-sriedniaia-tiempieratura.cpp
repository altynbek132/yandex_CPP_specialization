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
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

int main() {
    std::size_t N;
    cin>>N;
    vector<int> v;
    int sum = 0;
    for (int i = 0; i <N; ++i) {
        int t;
        cin>>t;
        sum+=t;
        v.push_back(t);
    }
    vi up;
    for (int j = 0; j < N; ++j) {
        auto t = v[j];
        if (t*N > sum) {
            up.push_back(j);
        }
    }
    std::cout << up.size() << std::endl;
    for (int i = 0; i < up.size(); ++i) {
        std::cout << up[i] << ' ';
    }



    return 0;
}
