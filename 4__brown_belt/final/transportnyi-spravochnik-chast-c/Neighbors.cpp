#include "Neighbors.h"

using namespace std;

size_t hash<Neighbors>::operator()(const Neighbors& obj) const {
    static const size_t x = 228'1488 + 54'27;
    size_t r1 = string_hash(obj.first);
    size_t r2 = string_hash(obj.second);
    return PolynomicCombine(x, {r1 + r2});
}
bool Neighbors::operator==(const Neighbors& rhs) const {
    auto lhs_neighbor_min = min(first, second);
    auto lhs_neighbor_max = max(first, second);
    auto rhs_neighbor_min = min(rhs.first, rhs.second);
    auto rhs_neighbor_max = max(rhs.first, rhs.second);
    return std::tie(lhs_neighbor_min, lhs_neighbor_max) == std::tie(rhs_neighbor_min, rhs_neighbor_max);
}
bool Neighbors::operator!=(const Neighbors& rhs) const {
    return !(rhs == *this);
}
