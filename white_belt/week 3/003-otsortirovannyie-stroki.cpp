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

class SortedStrings {
 public:
  void AddString(const string &s) {
    // добавить строку s в набор
    _s.insert(s);
  }
  vector<string> GetSortedStrings() {
    return {_s.begin(), _s.end()};
    // получить набор из всех добавленных строк в отсортированном порядке
  }
 private:
  multiset<string> _s;
  // приватные поля
};

void PrintSortedStrings(SortedStrings &strings) {
  for (const string &s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main() {
  SortedStrings strings;
  
  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  return 0;
}
