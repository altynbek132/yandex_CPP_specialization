#ifdef MASLO
#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif


#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

// Prerun maslo for cin&cout to txt; and tests are at beginning of file
// open

int main() {
    std::cout << "001" << std::endl;
    vector<int> a = {1, 2, 3, 4};
    
    std::cout << a << std::endl;
    AssertEqual(a, a);
    
    return 0;
}
