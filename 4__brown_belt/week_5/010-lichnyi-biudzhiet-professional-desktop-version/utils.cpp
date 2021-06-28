#include "utils.h"

using namespace std;

bool CheckAndSkip(istream& is, char ch) {
    if (is.peek() != ch) {
        return false;
    }
    is.ignore();
    return true;
}
bool CheckBounds(int val, int lower, int upper) {
    return lower <= val && val < upper;
}
