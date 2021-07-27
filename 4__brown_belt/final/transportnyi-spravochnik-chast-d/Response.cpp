#include "Response.h"

using namespace std;

namespace Response {

std::ostream& operator<<(ostream& os, const Holder& response_holder) {
    return os << response_holder->ToJson();
}

std::ostream& operator<<(std::ostream& out, const Base& response) {
    response.print(out);
    return out;
}

void BusRouteFound::print(std::ostream& os) const {
    // example:
    // Bus X: R stops on route, U unique stops, L route length, C curvature
    os << "Bus " << bus_name                          //
       << ": " << stops_count << " stops on route, "  //
       << unique_stops_count << " unique stops, "     //
       << route_length << " route length, "           //
       << curvature << " curvature";
}
Json::Node BusRouteFound::ToJson() const {
    /*
  {
    "route_length": 5950,
    "request_id": 1965312327,
    "curvature": 1.36124,
    "stop_count": 6,
    "unique_stop_count": 5
  },
     * */
    using namespace Json;
    map<string, Node> result;
    result.emplace("route_length", route_length);
    result.emplace("request_id", request_id);
    result.emplace("curvature", curvature);
    result.emplace("stop_count", static_cast<int>(stops_count));
    result.emplace("unique_stop_count", static_cast<int>(unique_stops_count));
    return Node(move(result));
}

void BusRouteNotFound::print(std::ostream& os) const {
    // example:
    // Bus 751: not found
    os << "Bus " << bus_name << ": not found";
}
Json::Node BusRouteNotFound::ToJson() const {
    /*
  {
    "request_id": 194217464,
    "error_message": "not found"
  },
     * */
    using namespace Json;
    map<string, Node> result;
    result.emplace("request_id", request_id);
    result.emplace("error_message", "not found"s);
    return Node(move(result));
}

void BusStopFound::print(std::ostream& os) const {
    // example:
    // Stop X: buses bus1 bus2 ... busN
    os << "Stop " << stop_name << ": buses";
    for (auto& bus_name : *bus_names) {
        os << " " << bus_name;
    }
}
Json::Node BusStopFound::ToJson() const {
    /*
  {
    "buses": [
      "256",
      "828"
    ],
    "request_id": 1042838872
  }
     * */
    using namespace Json;
    map<string, Node> result;
    result.emplace("request_id", request_id);

    vector<Node> buses;
    buses.reserve(bus_names->size());
    for (auto& bus_name : *bus_names) {
        buses.emplace_back(bus_name);
    }
    result.emplace("buses", buses);
    return Node(move(result));
}

void BusStopNotFound::print(std::ostream& os) const {
    // example:
    // Stop X: not found
    os << "Stop " << stop_name << ": not found";
}
Json::Node BusStopNotFound::ToJson() const {
    /*
  {
    "request_id": 746888088,
    "error_message": "not found"
  },
     * */
    using namespace Json;
    map<string, Node> result;
    result.emplace("request_id", request_id);
    result.emplace("error_message", "not found"s);
    return Node(move(result));
}

void BusStopEmpty::print(std::ostream& os) const {
    // example:
    // Stop X: no buses
    os << "Stop " << stop_name << ": no buses";
}
Json::Node BusStopEmpty::ToJson() const {
    /*
  {
    "buses": [],
    "request_id": 65100610
  },
     * */

    using namespace Json;
    map<string, Node> result;
    result.emplace("request_id", request_id);
    result.emplace("buses", vector<Node>{});
    return Node(move(result));
}

}  // namespace Response
