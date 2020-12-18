#include <bits/stdc++.h>

using namespace std;

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
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================


template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    auto maxIt = last;
    while (first != last) {
        if (pred(*first) && (maxIt == last || *first > *maxIt)) {
            maxIt = first;
        }
        first++;
    }
    return maxIt;
}


int main() {
    
    return 0;
}


// ==========================================
