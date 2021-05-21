#include <readFromInputTxt.h>
#include <iostream>

#ifdef MASLO

void txt(bool reopenInput, bool reopenOutput, bool turnOffSync) {
    if (reopenOutput) {
        std::cout << "output: output.txt" << std::endl;
    }
    if (reopenInput) {
        std::cout << "input: input.txt" << std::endl;
    }
    if (turnOffSync) {
        std::cout << "sync is turned off" << std::endl;
    }

    if (reopenOutput) {
        std::freopen("output.txt", "w", stdout);
    }
    if (reopenInput) {
        std::freopen("input.txt", "r", stdin);
    }
    if (turnOffSync) {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }
}

#endif  // MASLO
