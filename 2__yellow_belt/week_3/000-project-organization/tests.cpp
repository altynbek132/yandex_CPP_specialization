//
// Created by Addmin on 10.12.2020.
//

#include "tests.h"
#include "solution.h"

void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> unifdouble(-10, 10);
    std::uniform_int_distribution<int> unifint(-10, 10);
    
    for (size_t i = 0; i < 100; ++i) {
        int a = unifint(gen), b = unifint(gen);
        AssertEqual(sum(a, b), a + b);
        bool is_true = sum(a, b) == a + b;
        Assert(is_true);
    }
}


// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
    }
}
