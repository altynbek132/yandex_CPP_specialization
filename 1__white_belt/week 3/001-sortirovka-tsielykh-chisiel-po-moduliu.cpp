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

int main() {
  int N;
  cin >> N;
  vector<int> v;
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    v.push_back(x);
  }
  sort(v.begin(), v.end(), [](int l, int r) { return abs(l) < abs(r); });
  for (auto &x : v) {
    std::cout << x << " ";
  }
  
  return 0;
}





