#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

int main(int argc, const char** argv) {
    size_t n;
    cin >> n;
    list<int> seq;
    map<int, list<int>::iterator> num_to_it;

    while (n--) {
        int num, num_prev;
        cin >> num >> num_prev;
        auto it = num_to_it.find(num_prev);
        if (it == num_to_it.end()) {
            seq.push_back(num);
            num_to_it[num] = prev(seq.end());
        } else {
            auto new_pos = seq.insert(num_to_it[num_prev], num);
            num_to_it[num] = new_pos;
        }
    }

    for (auto& e : seq) {
        std::cout << e << std::endl;
    }

    return 0;
}
