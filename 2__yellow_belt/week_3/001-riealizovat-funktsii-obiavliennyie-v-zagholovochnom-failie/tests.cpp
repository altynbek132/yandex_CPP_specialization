//
// Created by Addmin on 10.12.2020.
//

#include "tests.h"
#include "solution.h"

#include "sum_reverse_sort.h"


void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> unifdouble(-10, 10);
    std::uniform_int_distribution<int> unifint(-10, 10);
    
    AssertEqual(Reverse("asdf "), " fdsa");
    vector<int> v;
    for (size_t i = 0; i < 100; ++i) {
        v.push_back(unifint(gen));
    }
    auto sorted = v;
    sort(sorted.begin(), sorted.end());
    Sort(v);
    AssertEqual(v, sorted);
    
    for (size_t i = 0; i < 100; ++i) {
        int a = unifint(gen);
        int b = unifint(gen);
        AssertEqual(Sum(a, b), a + b);
    }
}


// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
    }
}
