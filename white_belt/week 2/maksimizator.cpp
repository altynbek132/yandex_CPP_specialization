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

void UpdateIfGreater(int first, int& second) {
    if (first> second) {
        second = first;
    }
}

int main() {
    int a = 4, b=2;
    UpdateIfGreater(a,b);
    std::cout << b << std::endl;
    return 0;
}
