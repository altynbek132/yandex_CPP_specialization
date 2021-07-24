#include "Request.h"
#include "utils.h"

namespace Request {

RequestBase::RequestBase(RequestBase::Type type) : type(type) {}
RequestHolder RequestBase::Create(RequestBase::Type type) {
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
void AddBusStop::ParseFrom(string_view input) {}
void AddBusStop::Process(BusManager& manager) const {
    manager.AddBusStop(stop);
}
AddBusStop::AddBusStop() : ModifyRequest(RequestBase::Type::ADD_BUS_STOP) {}

//
void AddBusRoute::ParseFrom(string_view input) {}
void AddBusRoute::Process(BusManager& manager) const {
    manager.AddBusRoute(bus_route);
}
AddBusRoute::AddBusRoute() : ModifyRequest(RequestBase::Type::ADD_BUS_ROUTE) {}

//
void ReadBusRouteInfo::ParseFrom(string_view input) {}
ReadBusRouteInfoResultType ReadBusRouteInfo::Process(const BusManager& manager) const {
    return manager.ReadBusRouteInfo(bus_name);
}
ReadBusRouteInfo::ReadBusRouteInfo() : ReadRequest(RequestBase::Type::READ_BUS_ROUTE) {}

//
optional<RequestBase::Type> ConvertRequestTypeFromString(string_view type_str, OperationType operation_type) {
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
