#ifdef MASLO

#include "tests.h"
#include "solution.h"
#include <bits/stdc++.h>

using namespace std;

string gen_random(const int len) {
    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    tmp_s.reserve(len);
    
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> dd(-10, 10);
    std::uniform_int_distribution<int> ii(-10, 10);
    ASSERT(true);
    ASSERT_EQUAL(2 + 2, 4);
}

// this function is entry for testing
void TestAll() {
    {
        TestRunner tr;
        RUN_TEST(tr, basic_test);
    }
}

#endif
