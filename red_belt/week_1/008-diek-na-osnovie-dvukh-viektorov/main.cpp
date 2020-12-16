#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
//      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================

#include "test_runner.h"
#include "Deque.h"
#include <deque>

void exceptionThrowing() {
    Deque<int> d;
    deque<int> dd;
    
    try {
        ASSERT_EQUAL(d[0], dd[0]);
        ASSERT(false); //should not get to that line
    } catch (out_of_range &ex) {
    } catch (...) {
        ASSERT(false); //should throw only out_of_range
    }
    try {
        d.Back();
        ASSERT(false); //should not get to that line
    } catch (out_of_range &ex) {
    } catch (...) {
        ASSERT(false); //should throw only out_of_range
    }
    try {
        d.Front();
        ASSERT(false); //should not get to that line
    } catch (out_of_range &ex) {
    } catch (...) {
        ASSERT(false); //should throw only out_of_range
    }
}


void DequeTest() {
    Deque<int> d;
    deque<int> dd;
    
    
    for (size_t i = 0; i < 100; ++i) {
        ASSERT_EQUAL(d.Empty(), dd.empty());
        ASSERT_EQUAL(d.Size(), dd.size());
        
        if (i % 3 == 0) {
            d.PushFront(i);
            dd.push_front(i);
        } else {
            d.PushBack(i);
            dd.push_back(i);
        }
        if (d.Size() > 54) {
            ASSERT_EQUAL(d.Front(), dd.front());
            ASSERT_EQUAL(d.Back(), dd.back());
        }
    }
    
    {
        const int val = 1488228;
        const vector<int> changeIndexes = {54, 27, 1488 / 228};
        for (size_t change_index : changeIndexes) {
            d[change_index] = val;
            dd[change_index] = val;
        }
        
        
        const auto constD = d;
        
        for (size_t i = 0; i < d.Size(); ++i) {
            ASSERT_EQUAL(constD[i], dd[i]);
        }
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, DequeTest);
    RUN_TEST(tr, exceptionThrowing);
    
    return 0;
}


// ==========================================
