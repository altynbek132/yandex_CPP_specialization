// ==========================================
// sample for main:

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// #include <bits/stdc++.h>
//
//#include <cstdlib>
//#include <iostream>
//
//#include <set>
//#include <map>
//#include <deque>
//#include <sstream>
//#include <string>
//#include <iterator>
//#include <tuple>
//#include <algorithm>
//#include <utility>
//#include <vector>

//#include <numeric>
//
//#include <iomanip>
//#include <fstream>
//
//#include <type_traits>
//
//#include <limits>
//
//#include <cassert>
//#include <random>


using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
//      txt();
      TestAll();
  }
};

Prerun maslo;
#endif


int main() {
    vector<int> asdf = {1, 3, 4};
    std::cout << *asdf.begin()++ << std::endl;
    return 0;
}


// ==========================================
