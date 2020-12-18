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


class Person {
 public:
  void ChangeFirstName(int year, const string &first_name) {
      // добавить факт изменения имени на first_name в год year
      _year_to_first_name[year] = first_name;
  }
  
  void ChangeLastName(int year, const string &last_name) {
      // добавить факт изменения фамилии на last_name в год year
      _year_to_last_name[year] = last_name;
  }
  
  string GetFullName(int year) {
      // получить имя и фамилию по состоянию на конец года year
      string first = find_closest(year, _year_to_first_name);
      string last = find_closest(year, _year_to_last_name);
      if (first.empty() && last.empty()) {
          return "Incognito";
      }
      if (first.empty()) {
          return last + " with unknown first name";
      }
      if (last.empty()) {
          return first + " with unknown last name";
      }
      return first + " " + last;
  }
 
 private:
  // приватные поля
  map<int, string> _year_to_first_name;
  map<int, string> _year_to_last_name;
  
  static string find_closest(int year_, const map<int, string> &m_) {
      string closest;
      auto it = m_.upper_bound(year_);
      if (it != m_.begin()) {
          closest = (--it)->second;
      }
      
      return closest;
  }
};



int main() {
    
    
    return 0;
}


// ==========================================
