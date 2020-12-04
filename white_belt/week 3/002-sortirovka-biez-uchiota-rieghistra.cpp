//
// Created by Addmin on 03.12.2020.
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

string tolower_string(const string &_str) {
  auto str = _str;
  for_each(str.begin(), str.end(), [](char &ch) { ch = tolower(ch); });
  return str;
}

int main() {
  int N;
  cin >> N;
  vs v;
  for (size_t i = 0; i < N; ++i) {
    string str;
    cin >> str;
    v.push_back(str);
  }
  sort(v.begin(), v.end(), [](const string &left, const string &right) {
    return tolower_string(left) < tolower_string(right);
  });
  
  for (auto &str : v) {
    std::cout << str << " ";
  }
  
  return 0;
}
