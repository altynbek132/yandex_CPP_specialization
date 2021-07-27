#include "Request.h"
#include <exception>
#include "output_reload.h"
#include "utils.h"

using namespace std;

namespace Request {

Base::Base(Base::Type type) : type(type) {}
Holder Base::Create(Base::Type type) {
    switch (type) {
        case Type::ADD_BUS_ROUTE: {
            return make_unique<AddBusRoute>();
        }
        case Type::ADD_BUS_STOP: {
            return make_unique<AddBusStop>();
        }
        case Type::READ_BUS_ROUTE: {
            return make_unique<ReadBusRouteInfo>();
        }
        case Type::READ_BUS_STOP: {
            return make_unique<ReadBusStopInfo>();
        }
        default:
            return nullptr;
    }
}
std::ostream& operator<<(std::ostream& out, const Base& request) {
    request.print(out);
    return out;
}

//
void AddBusStop::ConvertFrom(const map<string, Json::Node>& input) {
    auto& road_distances = input.at("road_distances").AsMap();
    for (auto& [neigbor_stop_name, distance_node] : road_distances) {
        stop.distances_to_neighbor_stops.push_back({
            .distance = distance_node.AsInt(),
            .stop_name = neigbor_stop_name,
        });
    }
    stop.name = input.at("name").AsString();
    stop.coordinate = {
        .latitude = input.at("latitude").AsDouble(),
        .longitude = input.at("longitude").AsDouble(),
    };
}
void AddBusStop::Process(BusManager& manager) const {
    manager.AddBusStop(stop);
}
AddBusStop::AddBusStop() : Modify(Base::Type::ADD_BUS_STOP) {}
void AddBusStop::print(ostream& os) const {
    os << "AddBusStop: " << stop;
}

//
void AddBusRoute::ConvertFrom(const map<string, Json::Node>& input) {
    bus_route.bus_name = input.at("name").AsString();
    bus_route.type = input.at("is_roundtrip").AsBool() ? BusRoute::Type::LOOPED : BusRoute::Type::STRAIGHT;
    for (auto& stop_name_node : input.at("stops").AsArray()) {
        bus_route.stop_names.push_back(stop_name_node.AsString());
    }
    if (bus_route.type == BusRoute::Type::LOOPED) {
        if (bus_route.stop_names.front() != bus_route.stop_names.back()) {
            std::stringstream error;
            error << "stop_first should be equal stop_last in looped route: " << bus_route.stop_names.front()
                  << " != " << bus_route.stop_names.back();
            throw std::invalid_argument(error.str());
        }
        bus_route.stop_names.pop_back();
    }

    bus_route.stop_names.shrink_to_fit();
}
void AddBusRoute::Process(BusManager& manager) const {
    manager.AddBusRoute(bus_route);
}
AddBusRoute::AddBusRoute() : Modify(Base::Type::ADD_BUS_ROUTE) {}
void AddBusRoute::print(ostream& os) const {
    os << "AddBusRoute: " << bus_route;
}

//
void ReadBusRouteInfo::ConvertFrom(const map<string, Json::Node>& input) {
    request_id = input.at("id").AsInt();
    bus_name = input.at("name").AsString();
}
Response::Holder ReadBusRouteInfo::Process(const BusManager& manager) const {
    return manager.ReadBusRouteInfo(bus_name, request_id);
}
ReadBusRouteInfo::ReadBusRouteInfo() : Read(Base::Type::READ_BUS_ROUTE) {}
void ReadBusRouteInfo::print(ostream& os) const {
    os << "ReadBusRouteInfo: " << bus_name;
}

//
ReadBusStopInfo::ReadBusStopInfo() : Read(Base::Type::READ_BUS_STOP) {}
void ReadBusStopInfo::ConvertFrom(const map<string, Json::Node>& input) {
    request_id = input.at("id").AsInt();
    stop_name = input.at("name").AsString();
}
Response::Holder ReadBusStopInfo::Process(const BusManager& manager) const {
    return manager.ReadBusStopInfo(stop_name, request_id);
}
void ReadBusStopInfo::print(ostream& os) const {
    os << "ReadBusStopInfo: " << stop_name;
}

//
optional<Base::Type> ConvertRequestTypeFromString(string_view type_str, OperationType operation_type) {
    const auto map_it = OPERATION_TYPE_TO_MAP.find(operation_type);
    if (map_it == OPERATION_TYPE_TO_MAP.end()) {
        return nullopt;
    }
    const auto& typing_map = map_it->second;
    const auto typing_it = typing_map->find(type_str);
    if (typing_it == typing_map->end()) {
        return nullopt;
    }
    return typing_it->second;
}
std::ostream& operator<<(ostream& out, Base::Type type) {
    switch (type) {
        case Base::Type::ADD_BUS_STOP: {
            out << "ADD_BUS_STOP";
            break;
        }
        case Base::Type::ADD_BUS_ROUTE: {
            out << "ADD_BUS_ROUTE";
            break;
        }
        case Base::Type::READ_BUS_ROUTE: {
            out << "READ_BUS_ROUTE";
            break;
        }
        case Base::Type::READ_BUS_STOP: {
            out << "READ_BUS_STOP";
            break;
        }

        default:
            throw runtime_error("chotam?");
    }
    return out;
}

}  // namespace Request
