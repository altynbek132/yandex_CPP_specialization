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

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    string str(1, prefix);
    return equal_range(range_begin, range_end, str, [](const string &v, const string &pref) {
      if (v.empty()) { return true; }
      return v[0] < pref[0];
    });
}


template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix) {
    string end = prefix;
    end[end.length() - 1]++;
    return {lower_bound(range_begin, range_end, prefix),
            lower_bound(range_begin, range_end, end)};
}


int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
    
    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
         (mt_result.second - begin(sorted_strings)) << endl;
    
    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
         (na_result.second - begin(sorted_strings)) << endl;
    
    
    return 0;
}


// ==========================================
