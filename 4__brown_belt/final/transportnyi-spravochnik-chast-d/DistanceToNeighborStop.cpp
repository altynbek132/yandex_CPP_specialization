#include "DistanceToNeighborStop.h"
std::ostream& operator<<(std::ostream& os, const DistanceToNeighborStop& stop) {
    os << "distance: " << stop.distance << " stop_name: " << stop.stop_name;
    return os;
}
