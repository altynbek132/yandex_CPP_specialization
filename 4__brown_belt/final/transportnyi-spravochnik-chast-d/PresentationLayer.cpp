#include "PresentationLayer.h"
#include "json.h"

using namespace std;

Request::Holder ConvertJsonToRequest(const map<string, Json::Node>& json_request,
                                     Request::OperationType operation_type) {
    using namespace Request;

    auto request_type = ConvertRequestTypeFromString(json_request.at("type").AsString(), operation_type);
    if (!request_type) {
        return nullptr;
    }
    auto request = Base::Create(*request_type);
    if (request) {
        request->ConvertFrom(json_request);
    }
    return request;
}
vector<Request::Holder> ReadRequests(const vector<Json::Node>& request_nodes,
                                     Request::OperationType operation_type) {
    auto request_count = request_nodes.size();
    vector<Request::Holder> requests;
    requests.reserve(request_count);
    for (auto& request_node : request_nodes) {
        if (auto request = ConvertJsonToRequest(request_node.AsMap(), operation_type)) {
            requests.push_back(move(request));
        }
    }
    return requests;
}
ResponsesContainer ProcessRequests(const vector<Request::Holder>& requests, BusManager& manager) {
    ResponsesContainer responses;

    for (auto& request_holder : requests) {
        auto type = request_holder->type;
        if (type == Request::Base::Type::ADD_BUS_STOP) {
            const auto& request = dynamic_cast<const Request::AddBusStop&>(*request_holder);
            request.Process(manager);
        } else if (type == Request::Base::Type::ADD_BUS_ROUTE) {
            const auto& request = dynamic_cast<const Request::AddBusRoute&>(*request_holder);
            request.Process(manager);
        } else if (type == Request::Base::Type::READ_BUS_ROUTE) {
            const auto& request = dynamic_cast<const Request::ReadBusRouteInfo&>(*request_holder);
            responses.push_back(request.Process(manager));
        } else if (type == Request::Base::Type::READ_BUS_STOP) {
            const auto& request = dynamic_cast<const Request::ReadBusStopInfo&>(*request_holder);
            responses.push_back(request.Process(manager));
        } else {
            throw runtime_error("unknown request type");
        }
    }
    return responses;
}
void PrintResponses(const ResponsesContainer& responses, ostream& stream) {
    for (const auto& response : responses) {
        stream << *response << endl;
    }
}
