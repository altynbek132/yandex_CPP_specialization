#pragma once
#include <bits/stdc++.h>
#include <ostream>
#include "BusManager.h"
#include "BusRoute.h"
#include "BusStop.h"
#include "Coordinate.h"
#include "Response.h"
#include "json.h"

namespace Request {

struct Base;

using Holder = std::unique_ptr<Base>;

struct Base {
    enum class Type {
        ADD_BUS_STOP,
        ADD_BUS_ROUTE,
        READ_BUS_ROUTE,
        READ_BUS_STOP,
    };

    const Type type;

    explicit Base(Type type);
    static Holder Create(Type type);
    virtual void ConvertFrom(const map<string, Json::Node>&) = 0;
    virtual ~Base() = default;

    virtual void print(std::ostream& os) const = 0;
};
std::ostream& operator<<(std::ostream& out, const Base& request);
std::ostream& operator<<(std::ostream& out, Base::Type type);

/* ========================================================
TWO MAIN TYPES OF REQUEST (READ/MODIFY DB)
======================================================== */
template <typename ResultType>
struct Read : Base {
    using Base::Base;
    int request_id = -1;
    virtual ResultType Process(const BusManager& manager) const = 0;
};

struct Modify : Base {
    using Base::Base;
    virtual void Process(BusManager& manager) const = 0;
};
// ========================================================

struct AddBusStop : Modify {
    BusStop stop;
    explicit AddBusStop();
    void ConvertFrom(const map<string, Json::Node>&) override;
    void Process(BusManager& manager) const override;
    void print(std::ostream& os) const override;
};
struct AddBusRoute : Modify {
    BusRoute bus_route;
    explicit AddBusRoute();
    void ConvertFrom(const map<string, Json::Node>&) override;
    void Process(BusManager& manager) const override;
    void print(std::ostream& os) const override;
};

struct ReadBusRouteInfo : Read<Response::Holder> {
    std::string bus_name;
    ReadBusRouteInfo();
    void ConvertFrom(const map<string, Json::Node>&) override;
    Response::Holder Process(const BusManager& manager) const override;
    void print(std::ostream& os) const override;
};

struct ReadBusStopInfo : Read<Response::Holder> {
    std::string stop_name;
    ReadBusStopInfo();
    void ConvertFrom(const map<string, Json::Node>&) override;
    Response::Holder Process(const BusManager& manager) const override;
    void print(std::ostream& os) const override;
};

using Map_Type = std::unordered_map<std::string_view, Base::Type>;
inline const Map_Type STR_TO_MODIFY_REQUEST_TYPE = {
    {"Stop", Base::Type::ADD_BUS_STOP},
    {"Bus", Base::Type::ADD_BUS_ROUTE},
};
inline const Map_Type STR_TO_READ_REQUEST_TYPE = {
    {"Bus", Base::Type::READ_BUS_ROUTE},
    {"Stop", Base::Type::READ_BUS_STOP},
};

enum class OperationType {
    MODIFY,
    READ,
};

inline const std::unordered_map<OperationType, const Map_Type*> OPERATION_TYPE_TO_MAP = {
    {OperationType::MODIFY, &STR_TO_MODIFY_REQUEST_TYPE},
    {OperationType::READ, &STR_TO_READ_REQUEST_TYPE},
};

std::optional<Base::Type> ConvertRequestTypeFromString(std::string_view type_str,
                                                       OperationType operation_type);

}  // namespace Request