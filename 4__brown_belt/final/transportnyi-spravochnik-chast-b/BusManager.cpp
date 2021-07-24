#include "BusManager.h"

using namespace std;

void BusManager::AddBusRoute(BusRoute bus_route) {
    bus_name_to_bus_route[bus_route.bus_name] = bus_route;
    for (auto& stop_name : bus_route.stop_names) {
        bus_stop_name_to_bus_names[stop_name].insert(bus_route.bus_name);
    }
}
void BusManager::AddBusStop(BusStop bus_stop) {
    bus_stop_name_to_coordinate[bus_stop.name] = bus_stop.coordinate;
    bus_stop_name_to_bus_names[bus_stop.name];
}
Response::Holder BusManager::ReadBusRouteInfo(string_view bus_name) const {
    auto it = bus_name_to_bus_route.find(string(bus_name));
    if (it == bus_name_to_bus_route.end()) {
        auto response = make_shared<Response::BusRouteNotFound>();
        response->bus_name = bus_name;
        return response;
    }

    auto& bus_route = it->second;

    if (!bus_route.unique_stops_count.has_value()) {
        bus_route.unique_stops_count =
            unordered_set(bus_route.stop_names.begin(), bus_route.stop_names.end()).size();
    }

    if (!bus_route.route_length.has_value()) {
        double route_length = 0;
        for (size_t i = 1; i < bus_route.stop_names.size(); ++i) {
            auto& cur = bus_route.stop_names[i];
            auto& prev = bus_route.stop_names[i - 1];
            auto& cur_coord = bus_stop_name_to_coordinate.at(cur);
            auto& prev_coord = bus_stop_name_to_coordinate.at(prev);
            route_length += prev_coord.DistanceTo(cur_coord);
        }
        bus_route.route_length = route_length;
        switch (bus_route.type) {
            case BusRoute::Type::STRAIGHT: {
                bus_route.route_length.value() *= 2;
                break;
            }
            case BusRoute::Type::LOOPED: {
                auto& front = bus_stop_name_to_coordinate.at(bus_route.stop_names.front());
                auto& back = bus_stop_name_to_coordinate.at(bus_route.stop_names.back());
                bus_route.route_length.value() += back.DistanceTo(front);
                break;
            }
            default:
                throw runtime_error("chotam?");
        }
    }

    auto response = make_shared<Response::BusRouteFound>();
    response->bus_name = bus_name;
    response->stops_count = bus_route.getStopsCount();
    response->unique_stops_count = bus_route.unique_stops_count.value();
    response->route_length = bus_route.route_length.value();
    return response;
}
Response::Holder BusManager::ReadBusStopInfo(std::string_view stop_name) const {
    auto it = bus_stop_name_to_bus_names.find(string(stop_name));
    if (it == bus_stop_name_to_bus_names.end()) {
        auto response = make_shared<Response::BusStopsNotFound>();
        response->stop_name = stop_name;
        return response;
    }

    auto& bus_names = it->second;

    if (bus_names.empty()) {
        auto response = make_shared<Response::BusStopsEmpty>();
        response->stop_name = stop_name;
        return response;
    }

    auto response = make_shared<Response::BusStopsFound>();
    response->stop_name = stop_name;
    response->bus_names = &bus_names;
    return response;
}
