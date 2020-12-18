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
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================


#include "student.h"
#include "test_runner.h"

#include <algorithm>

using namespace std;

//Оптимизируйте эту функцию
bool Compare(const Student &first, const Student &second) {
    return first.Less(second);
}

void TestComparison() {
    Student newbie{
        "Ivan", "Ivanov", {
            {"c++", 1.0},
            {"algorithms", 3.0}
        },
        2.0
    };
    
    Student cpp_expert{
        "Petr", "Petrov", {
            {"c++", 9.5},
            {"algorithms", 6.0}
        },
        7.75
    };
    
    Student guru{
        "Sidor", "Sidorov", {
            {"c++", 10.0},
            {"algorithms", 10.0}
        },
        10.0
    };
    ASSERT(Compare(guru, newbie));
    ASSERT(Compare(guru, cpp_expert));
    ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
    vector<Student> students{
        {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
        {"Semen", "Semenov", {{"maths", 4.}}, 4.},
        {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
        {"Petr", "Petrov", {{"maths", 3.}}, 3.},
        {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
    };
    sort(students.begin(), students.end(), Compare);
    ASSERT(is_sorted(students.begin(), students.end(),
                     [](Student first, Student second) {
                       return first.Less(second);
                     })
    );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestComparison);
    RUN_TEST(tr, TestSorting);
    return 0;
}

// ==========================================
