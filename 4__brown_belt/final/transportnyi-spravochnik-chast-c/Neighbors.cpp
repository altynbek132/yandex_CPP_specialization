#include "Neighbors.h"

using namespace std;

size_t hash<Neighbors>::operator()(const Neighbors& obj) const {
    static const size_t x = 228'1488 + 54'27;
    size_t r1 = string_hash(obj.first);
    size_t r2 = string_hash(obj.second);
    return PolynomicCombine(x, {r1, r2});
}
bool Neighbors::operator==(const Neighbors& rhs) const {
    return std::tie(first, second) == std::tie(rhs.first, rhs.second);
}
bool Neighbors::operator!=(const Neighbors& rhs) const {
    return !(rhs == *this);
}
