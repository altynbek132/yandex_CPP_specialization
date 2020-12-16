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

#include "test_runner.h"

#include <ostream>

using namespace std;

#define PRINT_VALUES(out, x, y) (out << (x) << endl << (y) << endl)


int main() {
    TestRunner tr;
    tr.RunTest([] {
      ostringstream output;
      PRINT_VALUES(output, 5, "red belt");
      ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");
}

// ==========================================
