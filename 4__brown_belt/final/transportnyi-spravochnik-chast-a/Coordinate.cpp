#include "Coordinate.h"
#include "constants.h"

using namespace std;

/**
 * distance between two longitude-latitude coords
 *
 * formula:
 * https://www.movable-type.co.uk/scripts/latlong.html
 * */
double DistanceBetween(const Coordinate& first, const Coordinate& second) {
    const auto φ1 = first.latitude * PI / 180;  // φ, λ in radians
    const auto φ2 = second.latitude * PI / 180;
    const auto Δφ = (second.latitude - first.latitude) * PI / 180;
    const auto Δλ = (second.longitude - first.longitude) * PI / 180;

    const auto a = sin(Δφ / 2) * sin(Δφ / 2) + cos(φ1) * cos(φ2) * sin(Δλ / 2) * sin(Δλ / 2);
    const auto c = 2 * atan2(sqrt(a), sqrt(1 - a));

    const auto d = EARTH_RADIUS_KM * c;
}
double Coordinate::DistanceTo(const Coordinate& other) const {
    return DistanceBetween(*this, other);
}

/* ========================================================
BOILERPLATE
======================================================== */

size_t hash<Coordinate>::operator()(const Coordinate& obj) const {
    static const size_t x = 228'1488 + 54'27;
    size_t r1 = double_hash(obj.latitude);
    size_t r2 = double_hash(obj.longitude);
    return PolynomicCombine(x, {r1, r2});
}
