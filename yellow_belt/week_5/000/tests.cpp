#ifdef MASLO
//
// Created by Addmin on 10.12.2020.
//

#include "tests.h"
#include "solution.h"

#include <set>

using namespace std;

void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> unifdouble(-10, 10);
    std::uniform_int_distribution<int> unifint(-10, 10);
}


// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
    }
}

#endif
