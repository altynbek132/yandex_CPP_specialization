// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

using namespace std;

void txt() {
  const char *maslo = std::getenv("maslo");
  if (!maslo) {
    return;
  }
  
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)


int main() {
  txt();
  
  ifstream input("input.txt");
  if (!input) {
    exit(1);
  }
//
  
  int N, M;
  input >> N >> M;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      int num;
      input >> num;
      input.ignore(1);
      std::cout << setw(10) << num;
      if (j != M - 1) {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
  
  return 0;
}

