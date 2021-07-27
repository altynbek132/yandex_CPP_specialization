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
    for (auto& neighbor_stop_with_distance : bus_stop.distances_to_neighbor_stops) {
        neighbors_to_distance[{
            .first = bus_stop.name,
            .second = neighbor_stop_with_distance.stop_name,
        }] = neighbor_stop_with_distance.distance;
    }
}
Response::Holder BusManager::ReadBusRouteInfo(std::string_view bus_name, int request_id) const {
    auto it = bus_name_to_bus_route.find(string(bus_name));
    if (it == bus_name_to_bus_route.end()) {
        auto response = make_shared<Response::BusRouteNotFound>();
        response->request_id = request_id;
        response->bus_name = bus_name;
        return response;
    }

    auto& bus_route = it->second;

    if (!bus_route.unique_stops_count.has_value()) {
        bus_route.unique_stops_count =
            unordered_set(bus_route.stop_names.begin(), bus_route.stop_names.end()).size();
    }

    if (!bus_route.route_length.has_value() || !bus_route.curvature.has_value()) {
        bus_route.route_length = 0;
        auto& route_length = bus_route.route_length.value() = 0;
        double geographic_length = 0;
        for (size_t i = 1; i < bus_route.stop_names.size(); ++i) {
            auto& cur = bus_route.stop_names[i];
            auto& prev = bus_route.stop_names[i - 1];
            const auto [geographic_length_cur, real_distance_cur] =
                GetGeographicAndRealDistanceBetweenNeighbors(prev, cur);
            route_length += real_distance_cur;
            geographic_length += geographic_length_cur;
        }

        // post-calculation depending on type of route
        switch (bus_route.type) {
            case BusRoute::Type::STRAIGHT: {
                // starts EXCLUSIVELY, ends INCLUSIVELY
                for (size_t i = bus_route.stop_names.size() - 1; i-- > 0;) {
                    auto& cur = bus_route.stop_names[i];
                    auto& prev = bus_route.stop_names[i + 1];
                    const auto [geographic_length_cur, real_distance_cur] =
                    GetGeographicAndRealDistanceBetweenNeighbors(prev, cur);
                    route_length += real_distance_cur;
                    geographic_length += geographic_length_cur;
                }
                break;
            }
            case BusRoute::Type::LOOPED: {
                auto& front_stop_name = bus_route.stop_names.front();
                auto& back_stop_name = bus_route.stop_names.back();
                const auto [geographic_length_last, real_distance_last] =
                    GetGeographicAndRealDistanceBetweenNeighbors(back_stop_name, front_stop_name);
                route_length += real_distance_last;
                geographic_length += geographic_length_last;
                break;
            }
            default:
                throw runtime_error("chotam?");
        }
        bus_route.curvature = route_length / geographic_length;
    }

    auto response = make_shared<Response::BusRouteFound>();
    response->request_id = request_id;
    response->bus_name = bus_name;
    response->stops_count = bus_route.getStopsCount();
    response->unique_stops_count = bus_route.unique_stops_count.value();
    response->route_length = bus_route.route_length.value();
    response->curvature = bus_route.curvature.value();
    return response;
}
Response::Holder BusManager::ReadBusStopInfo(std::string_view stop_name, int request_id) const {
    auto it = bus_stop_name_to_bus_names.find(string(stop_name));
    if (it == bus_stop_name_to_bus_names.end()) {
        auto response = make_shared<Response::BusStopNotFound>();
        response->request_id = request_id;
        response->stop_name = stop_name;
        return response;
    }

    auto& bus_names = it->second;

    if (bus_names.empty()) {
        auto response = make_shared<Response::BusStopEmpty>();
        response->request_id = request_id;
        response->stop_name = stop_name;
        return response;
    }

    auto response = make_shared<Response::BusStopFound>();
    response->request_id = request_id;
    response->stop_name = stop_name;
    response->bus_names = &bus_names;
    return response;
}
pair<double, double> BusManager::GetGeographicAndRealDistanceBetweenNeighbors(std::string first,
                                                                              std::string second) const {
    auto& first_coord = bus_stop_name_to_coordinate.at(first);
    auto& second_coord = bus_stop_name_to_coordinate.at(second);
    const double geographic_distance = second_coord.DistanceTo(first_coord);

    if (auto real_distance_it = neighbors_to_distance.find({.first = first, .second = second});
        real_distance_it != neighbors_to_distance.end()) {
        return {geographic_distance, real_distance_it->second};
    }
    if (auto real_distance_it = neighbors_to_distance.find({.first = second, .second = first});
        real_distance_it != neighbors_to_distance.end()) {
        return {geographic_distance, real_distance_it->second};
    }
    return {geographic_distance, geographic_distance};
}
