#include "Responses.h"

namespace Response {

void BusRouteFound::print(ostream& os) const {
    // example:
    // Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length
    os << "Bus " << bus_name                          //
       << ": " << stops_count << " stops on route, "  //
       << unique_stops_count << " unique stops, "     //
       << route_length << " route length";
}

void BusRouteNotFound::print(ostream& os) const {
    // example:
    // Bus 751: not found
    os << "Bus " << bus_name << ": not found";
}
}  // namespace Response
