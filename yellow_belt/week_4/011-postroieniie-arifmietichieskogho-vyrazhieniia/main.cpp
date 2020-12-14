// ==========================================
// sample for main:

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <bits/stdc++.h>
//
//#include <cstdlib>
//#include <iostream>
//
//#include <set>
//#include <map>
//#include <deque>
//#include <sstream>
//#include <string>
//#include <iterator>
//#include <tuple>
//#include <algorithm>
//#include <utility>
//#include <vector>

//#include <numeric>
//
//#include <iomanip>
//#include <fstream>
//
//#include <type_traits>
//
//#include <limits>
//
//#include <cassert>
//#include <random>


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

#ifdef MASLO

#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
      txt();
//      TestAll();
  }
};

Prerun maslo;
#endif


struct OP {
  int num;
  char oper;
};

//int main() {
//    int x, N;
//    cin >> x >> N;
//    vector<OP> ops;
//    for (int i = 0; i < N; ++i) {
//        OP op;
//        cin >> op.oper >> op.num;
//        ops.push_back(op);
//    }
//
//    std::cout << string(ops.size(), '(') << x;
//    for (auto &op : ops) {
//        std::cout << ") " << op.oper << " " << op.num;
//    }
//
//    return 0;
//}

bool need_bracket(char prev, char current) {
    return (prev == '+' or prev == '-') and (current == '*' or current == '/');
}

int main() {
    int x, N;
    cin >> x >> N;
    vector<OP> ops;
    for (int i = 0; i < N; ++i) {
        OP op;
        cin >> op.oper >> op.num;
        ops.push_back(op);
    }
    
    deque<string> res;
    char prev_op = '*';
    res.push_back(to_string(x));
    for (auto &op: ops) {
        bool enclose = need_bracket(prev_op, op.oper);
        prev_op = op.oper;
        
        if (enclose) {
            res.emplace_front("(");
            res.emplace_back(")");
        }
        stringstream ss;
        ss << " " << op.oper << " " << op.num;
        res.push_back(ss.str());
    }
    
    std::copy(res.begin(), res.end(), std::ostream_iterator<string>(std::cout, ""));
    return 0;
}


// ==========================================
