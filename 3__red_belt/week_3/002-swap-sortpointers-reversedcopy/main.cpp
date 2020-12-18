#include <bits/stdc++.h>

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


#include "test_runner.h"

#include <algorithm>
#include <numeric>

using namespace std;

template<typename T>
void Swap(T *first, T *second) {
    swap(*first, *second);
}

template<typename T>
void SortPointers(vector<T *> &pointers) {
    sort(pointers.begin(), pointers.end(), [](const T *lhs, const T *rhs) { return *lhs < *rhs; });
}

template<typename T>
void ReversedCopy(T *source, size_t count, T *destination) {
    auto s_b = source, s_e = source + count, d_b = destination, d_e = destination + count;
    if (d_b >= s_e || d_e <= s_b) {
        reverse_copy(s_b, s_e, d_b);
    } else if (d_b > s_b) {
        for (size_t i = 0; s_b + i < d_b; ++i) {
            d_e[-1 - i] = s_b[i];
        }
        reverse(d_b, s_e);
    } else {
        for (size_t i = 0; s_e - 1 - i >= d_e; ++i) {
            d_b[i] = s_e[-1 - i];
        }
        reverse(s_b, d_e);
    }
}

void TestSwap() {
    int a = 1;
    int b = 2;
    Swap(&a, &b);
    ASSERT_EQUAL(a, 2);
    ASSERT_EQUAL(b, 1);
    
    string h = "world";
    string w = "hello";
    Swap(&h, &w);
    ASSERT_EQUAL(h, "hello");
    ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
    int one = 1;
    int two = 2;
    int three = 3;
    
    vector<int *> pointers;
    pointers.push_back(&two);
    pointers.push_back(&three);
    pointers.push_back(&one);
    
    SortPointers(pointers);
    
    ASSERT_EQUAL(pointers.size(), 3u);
    ASSERT_EQUAL(*pointers[0], 1);
    ASSERT_EQUAL(*pointers[1], 2);
    ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
    const size_t count = 7;
    
    int *source = new int[count];
    int *dest = new int[count];
    
    for (size_t i = 0; i < count; ++i) {
        source[i] = i + 1;
    }
    ReversedCopy(source, count, dest);
    const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
    ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);
    
    // Области памяти могут перекрываться
    ReversedCopy(source, count - 1, source + 1);
    const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
    ASSERT_EQUAL(vector<int>(source, source + count), expected2);
    
    delete[] dest;
    delete[] source;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSwap);
    RUN_TEST(tr, TestSortPointers);
    RUN_TEST(tr, TestReverseCopy);
    return 0;
}



// ==========================================
