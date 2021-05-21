#pragma once

#include <iostream>

#ifdef MASLO

void txt() {
    std::cout << "io: input.txt and output.txt" << std::endl;

    std::freopen("input.txt", "r", stdin);

    // return;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::freopen("output.txt", "w", stdout);
}

struct prerun {
    prerun() { txt(); }
};

#endif  // MASLO
