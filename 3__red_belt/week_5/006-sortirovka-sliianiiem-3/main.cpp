// #include <bits/stdc++.h>
// #include "profile.h"
// #include "test_runner.h"
//
// using namespace std;
//
// #ifdef MASLO
//
// prerun maslo(true, false, false);
//
// #endif  // MASLO

#include <algorithm>
#include <memory>
#include <vector>
#include "test_runner.h"

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    const size_t size = range_end - range_begin;
    if (size < 2) {
        return;
    }

    vector<typename RandomIt::value_type> all_elements{move_iterator(range_begin), move_iterator(range_end)};
    auto begin = all_elements.begin();
    auto one_third = begin + size / 3;
    auto two_third = begin + size * 2 / 3;

    MergeSort(begin, one_third);
    MergeSort(one_third, two_third);
    MergeSort(two_third, all_elements.end());

    vector<typename RandomIt::value_type> temp;
    temp.reserve(size * 2 / 3);
    merge(move_iterator(begin),
          move_iterator(one_third),  //
          move_iterator(one_third),  //
          move_iterator(two_third),  //
          (back_inserter(temp)));
    merge(move_iterator(temp.begin()),
          move_iterator(temp.end()),          //
          move_iterator(two_third),           //
          move_iterator(all_elements.end()),  //
          range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
