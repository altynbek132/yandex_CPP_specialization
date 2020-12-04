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
  int Q;
  cin >> Q;
  map<string, set<string>> dict;
  for (int i = 0; i < Q; ++i) {
    string operation_code;
    cin >> operation_code;
    if (operation_code == "ADD") {
      string word1, word2;
      cin >> word1 >> word2;
      dict[word1].insert(word2);
      dict[word2].insert(word1);
    } else if (operation_code == "COUNT") {
      string word;
      cin >> word;
      std::cout << dict[word].size() << std::endl;
    } else if (operation_code == "CHECK") {
      string word1, word2;
      cin >> word1 >> word2;
      if (dict[word1].count(word2)) {
        std::cout << "YES" << std::endl;
      } else {
        std::cout << "NO" << std::endl;
      }
    }
  }
  return 0;
}





