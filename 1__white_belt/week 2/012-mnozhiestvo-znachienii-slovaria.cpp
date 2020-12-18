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
set<string> BuildMapValuesSet(const map<int, string> &m) {
  // ...
  set<string> s;
  for (const auto &[key, value] :m) {
    s.insert(value);
  }
  return s;
}

//int main() {
//  set<string> values = BuildMapValuesSet({
//                                             {1, "odd"},
//                                             {2, "even"},
//                                             {3, "odd"},
//                                             {4, "even"},
//                                             {5, "odd"}
//                                         });
//
//  for (const string &value : values) {
//    cout << value << endl;
//  }
//  return 0;
//}





