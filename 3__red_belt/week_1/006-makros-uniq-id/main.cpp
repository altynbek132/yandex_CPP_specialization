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

#include <string>
#include <vector>

using namespace std;

#define UNIQ_ID_IMPL_2(lineno) _a_local_var_##lineno
#define UNIQ_ID_IMPL(lineno) UNIQ_ID_IMPL_2(lineno)
#define UNIQ_ID UNIQ_ID_IMPL(__LINE__)


int main() {
    int
    UNIQ_ID = 0;
    string
    UNIQ_ID = "hello";
    vector<string>
    UNIQ_ID = {"hello", "world"};
    vector<int>
    UNIQ_ID = {1, 2, 3, 4};
    
    auto a = 5;
    -- -- -- -- -- -- -- -- -- -- -- --a;
    std::cout << a << std::endl;
}



// ==========================================
