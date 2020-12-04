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

#include <numeric>

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
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// ==================================



// ==================================

int main() {
//  txt();

//  ifstream input("input.txt");
//  ofstream out("output.txt");
//  if (!input || !out) {
//    exit(1);
//  }
//
    stringstream asdf("--1  ");
    int a;
    asdf >> a;
    std::cout << "a: " << a << std::endl;
    std::cout << "error: " << asdf.eof() << std::endl;
    std::cout << "healthy: " << static_cast<bool>(asdf) << std::endl;
    
    return 0;
}
