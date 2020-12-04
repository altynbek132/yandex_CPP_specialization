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

#include <iomanip>
#include <fstream>


using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)


int main() {
  ifstream input("input.txt");
  
  if (!input) {
    exit(1);
  }
  
  string str;
  while (getline(input, str)) {
    std::cout << str << std::endl;
  }
  
  return 0;
}
