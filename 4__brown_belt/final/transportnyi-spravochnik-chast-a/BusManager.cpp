#include "BusManager.h"

using namespace std;

void BusManager::AddBusRoute(BusRoute bus_route) {
    bus_name_to_bus_route[bus_route.bus_name] = bus_route;
}
void BusManager::AddBusStop(BusStop bus_stop) {
    bus_stop_name_to_count[bus_stop.name]++;
    bus_stop_name_to_coordinate[bus_stop.name] = bus_stop.coordinate;
}
Response::Holder BusManager::ReadBusRouteInfo(string_view bus_name) const {
    auto it = bus_name_to_bus_route.find(string(bus_name));
    if (it == bus_name_to_bus_route.end()) {
        auto response = make_shared<Response::BusRouteNotFound>();
        response->bus_name = bus_name;
        return response;
    }

    auto& bus_route = it->second;

    auto stops_count = bus_route.stop_names.size();

    size_t unique_stops_count =
        count_if(bus_route.stop_names.begin(), bus_route.stop_names.end(),
                 [&](const auto& stop_name) { return bus_stop_name_to_count.at(stop_name) == 1; });

    if (!bus_route.route_length.has_value()) {
        // todo: depend on type
        double route_length = 0;
        for (size_t i = 1; i < stops_count; ++i) {
            auto& cur = bus_route.stop_names[i];
            auto& prev = bus_route.stop_names[i - 1];
            auto& cur_coord = bus_stop_name_to_coordinate.at(cur);
            auto& prev_coord = bus_stop_name_to_coordinate.at(prev);
            route_length += prev_coord.DistanceTo(cur_coord);
        }
        bus_route.route_length = route_length;
    }
    auto route_length = bus_route.route_length.value();

    auto response = make_shared<Response::BusRouteFound>();
    response->bus_name = bus_name;
    response->stops_count = stops_count;
    response->unique_stops_count = unique_stops_count;
    response->route_length = route_length;
    return response;
}
