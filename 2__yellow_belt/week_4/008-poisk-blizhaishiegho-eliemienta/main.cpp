// ==========================================
// sample for main:

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <bits/stdc++.h>
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
//      TestAll();
  }
};

Prerun maslo;
#endif

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border) {
    auto it = numbers.lower_bound(border);
    if (it == numbers.begin()) { return it; }
    if (it == numbers.end()) { return --it; }
    
    if (abs(*it - border) < abs(*prev(it) - border)) { return it; }
    else { return --it; }
}
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел


int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;
    
    set<int> empty_set;
    
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    
    return 0;
}


// ==========================================
