#pragma once
#include <bits/stdc++.h>
#include "BusManager.h"
#include "BusRoute.h"
#include "BusStop.h"
#include "Coordinate.h"

using namespace std;

namespace Request {

struct RequestBase;

using RequestHolder = unique_ptr<RequestBase>;

struct RequestBase {
    enum class Type {
        ADD_BUS_STOP,
        ADD_BUS_ROUTE,
        READ_BUS_ROUTE,
    };

    const Type type;

    explicit RequestBase(Type type);
    static RequestHolder Create(Type type);
    virtual void ParseFrom(string_view input) = 0;
    virtual ~RequestBase() = default;
};

template <typename ResultType>
struct ReadRequest : RequestBase {
    using RequestBase::RequestBase;
    virtual ResultType Process(const BusManager& manager) const = 0;
};

struct ModifyRequest : RequestBase {
    using RequestBase::RequestBase;
    virtual void Process(BusManager& manager) const = 0;
};

struct AddBusStop : ModifyRequest {
    BusStop stop;
    explicit AddBusStop();
    void ParseFrom(string_view input) override;
    void Process(BusManager& manager) const override;
};
struct AddBusRoute : ModifyRequest {
    BusRoute bus_route;
    explicit AddBusRoute();
    void ParseFrom(string_view input) override;
    void Process(BusManager& manager) const override;
};

struct ReadBusRouteInfoResultType {
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
};

struct ReadBusRouteInfo : ReadRequest<ReadBusRouteInfoResultType> {
    string bus_name;
    ReadBusRouteInfo();
    void ParseFrom(string_view input) override;
    ReadBusRouteInfoResultType Process(const BusManager& manager) const override;
};

using Map_Type = unordered_map<string_view, RequestBase::Type>;
const Map_Type STR_TO_MODIFY_REQUEST_TYPE = {
    {"Stop", RequestBase::Type::ADD_BUS_STOP},
    {"Bus", RequestBase::Type::ADD_BUS_ROUTE},
};
const Map_Type STR_TO_READ_REQUEST_TYPE = {
    {"Bus", RequestBase::Type::READ_BUS_ROUTE},
};

enum class OperationType {
    MODIFY,
    READ,
};

const unordered_map<OperationType, const Map_Type*> OPERATION_TYPE_TO_MAP = {
    {OperationType::MODIFY, &STR_TO_MODIFY_REQUEST_TYPE},
    {OperationType::READ, &STR_TO_READ_REQUEST_TYPE},
};

optional<RequestBase::Type> ConvertRequestTypeFromString(string_view type_str, OperationType operation_type);

}  // namespace Request