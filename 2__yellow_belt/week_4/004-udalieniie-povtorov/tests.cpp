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
    
    
    vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
    RemoveDuplicates(v1);
    for (int x : v1) {
        cout << x << " ";
    }
    cout << endl;
    
    vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
    RemoveDuplicates(v2);
    for (const string &s : v2) {
        cout << s << " ";
    }
    cout << endl;
}


// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
    }
}
