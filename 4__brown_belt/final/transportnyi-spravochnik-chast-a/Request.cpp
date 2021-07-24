#include "Request.h"
#include <exception>
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
        default:
            return nullptr;
    }
}

//
void AddBusStop::ParseFrom(string_view input) {
    auto initial_input = input;
    // Stop X: latitude, longitude

    Trim(input);
    ReadToken(input);
    const string_view stop_name = ReadToken(input);
    TrimLeft(input);
    const double latitude = ConvertToDouble(ReadToken(input));
    const double longitude = ConvertToDouble(ReadToken(input));
    if (!input.empty()) {
        stringstream error;
        error << "string " << initial_input << " contains " << input.size() << " trailing characters";
        throw invalid_argument(error.str());
    }
    stop.name = stop_name;
    stop.coordinate = {
        .latitude = latitude,
        .longitude = longitude,
    };
}
void AddBusStop::Process(BusManager& manager) const {
    manager.AddBusStop(stop);
}
AddBusStop::AddBusStop() : Modify(Base::Type::ADD_BUS_STOP) {}

//
void AddBusRoute::ParseFrom(string_view input) {
    auto initial_input = input;
    // Bus X: описание маршрута
    //
    // 1. stop1 - stop2 - ... - stopN: автобус следует от stop1 до stopN и обратно с указанными промежуточными
    // остановками.
    //
    // 2. stop1 > stop2 > ... > stopN > stop1: кольцевой маршрут с конечной stop1.
    Trim(input);
    ReadToken(input);
    TrimLeft(input);

    bus_route.bus_name = ReadToken(input, ":");

    TrimLeft(input);
    string delim;
    if (input.find('-') != string_view::npos) {
        bus_route.type = BusRoute::Type::STRAIGHT;
        delim = " - ";
    } else if (input.find('>') != string_view::npos) {
        bus_route.type = BusRoute::Type::LOOPED;
        delim = " > ";
    } else {
        std::stringstream error;
        error << "unknown bus route type (uknown delimiter) or invalid bus route: " << initial_input;
        throw std::invalid_argument(error.str());
    }

    while (!input.empty()) {
        auto stop_name = ReadToken(input, delim);
        Trim(stop_name);
        bus_route.stop_names.emplace_back(stop_name.data());
    }
    bus_route.stop_names.shrink_to_fit();
}
void AddBusRoute::Process(BusManager& manager) const {
    manager.AddBusRoute(bus_route);
}
AddBusRoute::AddBusRoute() : Modify(Base::Type::ADD_BUS_ROUTE) {}

//
void ReadBusRouteInfo::ParseFrom(string_view input) {
    auto initial_input = input;
    // Bus X
    Trim(input);
    ReadToken(input);
    TrimLeft(input);
    bus_name = ReadToken(input, "\n");
}
Response::Holder ReadBusRouteInfo::Process(const BusManager& manager) const {
    return manager.ReadBusRouteInfo(bus_name);
}
ReadBusRouteInfo::ReadBusRouteInfo() : Read(Base::Type::READ_BUS_ROUTE) {}

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

}  // namespace Request
