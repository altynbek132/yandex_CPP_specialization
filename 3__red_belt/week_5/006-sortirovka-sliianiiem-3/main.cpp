#include <bits/stdc++.h>
#include <profile.h>
#include <test_runner.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================


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

#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

class Logger {
 private:
  int value = 0;
 public:
  Logger() { std::cout << "def ctor" << std::endl; }
  
  bool operator<(const Logger &rhs) const {
      return value < rhs.value;
  }
  
  bool operator>(const Logger &rhs) const {
      return rhs < *this;
  }
  
  bool operator<=(const Logger &rhs) const {
      return !(rhs < *this);
  }
  
  bool operator>=(const Logger &rhs) const {
      return !(*this < rhs);
  }
  
  Logger(const Logger &) { std::cout << "copy ctor" << std::endl; }
  
  Logger(Logger &&) { std::cout << "move ctor" << std::endl; }
  
  Logger &operator=(const Logger &) { std::cout << "copy ASS" << std::endl; }
  
  Logger &operator=(Logger &&) { std::cout << "move ASS" << std::endl; }
};


template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) { return; }
    
    
    vector<typename RandomIt::value_type> v{move_iterator(range_begin), move_iterator(range_end)};
    auto step = (v.end() - v.begin()) / 3;
    
    MergeSort(v.begin(), v.begin() + step);
    MergeSort(v.begin() + step, v.begin() + step * 2);
    MergeSort(v.begin() + step * 2, v.end());
    
    vector<typename RandomIt::value_type> temp;
    temp.reserve(2 * step);
    std::merge(move_iterator(v.begin()), move_iterator(v.begin() + step),
               move_iterator(v.begin() + step), move_iterator(v.begin() + step * 2),
               (std::back_inserter(temp)));
    std::merge(move_iterator(temp.begin()), move_iterator(temp.end()),
               move_iterator(v.begin() + step * 2), move_iterator(v.end()),
               range_begin);
}



void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

void test() {
    vector<Logger> vl = {{}};
    vl.push_back({});
    vl.push_back({});
    MergeSort(vl.begin(), vl.end());
}

//void TestNoCopy() {
//    vector<StringNonCopyable> v;
//    v.push_back(StringNonCopyable("c"));
////    vector<StringNonCopyable> v = {StringNonCopyable("c"), "a", "b", "c", "a", "b", "c", "a", "b"};
//    MergeSort(v.begin(), v.end());
//}

int main() {
    TestRunner tr;
//    RUN_TEST(tr, test);
    RUN_TEST(tr, TestIntVector);
//    RUN_TEST(tr, TestNoCopy);
    return 0;
}

// ==========================================
