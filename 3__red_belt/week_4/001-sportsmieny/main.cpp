#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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



int main() {
#ifndef MASLO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    
    list<size_t> row;
    size_t MAX_SIZE = 100000;
    vector<list<size_t>::iterator> number_to_positions(MAX_SIZE + 1, row.end());
    size_t n;
    cin >> n;
    
    for (std::size_t i = 0; i < n; ++i) {
        size_t num, pos_num;
        cin >> num >> pos_num;
        number_to_positions[num] = row.insert(number_to_positions[pos_num], num);
    }
    copy(row.begin(), row.end(), ostream_iterator<size_t>(cout, "\n"));
    
    
    return 0;
}


// ==========================================
