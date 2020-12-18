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
      TestAll();
  }
};

Prerun maslo;
#endif


//template<typename RandomIt>
//void MergeSort(RandomIt range_begin, RandomIt range_end) {
//    if (range_end - range_begin < 2) { return; }
//
//    vector<typename RandomIt::value_type> v(range_begin, range_end);
//    auto mid = v.begin() + (v.end() - v.begin()) / 2;
//
//    MergeSort(v.begin(), mid);
//    MergeSort(mid, v.end());
//    std::merge(v.begin(), mid, mid, v.end(), range_begin);
//}

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) { return; }
    
    vector<typename RandomIt::value_type> v(range_begin, range_end);
    auto step = (v.end() - v.begin()) / 3;
    
    MergeSort(v.begin(), v.begin() + step);
    MergeSort(v.begin() + step, v.begin() + step * 2);
    MergeSort(v.begin() + step * 2, v.end());
    
    vector<typename RandomIt::value_type> temp;
    std::merge(v.begin(), v.begin() + step,
               v.begin() + step, v.begin() + step * 2,
               back_inserter(temp));
    std::merge(temp.begin(), temp.end(),
               v.begin() + step * 2, v.end(),
               range_begin);
}




int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}


// ==========================================
