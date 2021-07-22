#include <bits/stdc++.h>
#include "Request.h"
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

using namespace std;

Request::RequestHolder ParseRequest(string_view str) {
    using namespace Request;

    const auto [lhs, rhs] = SplitTwoStrict(str, ":");
    const OperationType operation_type = rhs ? OperationType::MODIFY : OperationType::READ;

    auto request_type = ConvertRequestTypeFromString(str, operation_type);
    if (!request_type) {
        return nullptr;
    }
    auto request = RequestBase::Create(*request_type);
    if (request) {
        request->ParseFrom(str);
    }
    return request;
}

vector<Request::RequestHolder> ReadRequests(istream& input = cin) {
    auto request_count = ReadNumberOnLine<size_t>(input);
    vector<Request::RequestHolder> requests;
    requests.reserve(request_count);
    for (size_t i = 0; i < request_count; ++i) {
        string request_str;
        getline(input, request_str);
        if (auto request = ParseRequest(request_str)) {
            requests.push_back(move(request));
        }
    }
    return requests;
}

using ResponsesContainer = vector<Request::ResultType>;
ResponsesContainer ProcessRequests(const vector<Request::RequestHolder>& requests) {
    ResponsesContainer responses;
    BusManager manager;

    for (auto& request_holder : requests) {
        auto type = request_holder->type;
        if (type == Request::RequestBase::Type::ADD_BUS_STOP) {
            const auto& request = dynamic_cast<const Request::AddBusStop&>(*request_holder);
            request.Process(manager);
        } else if (type == Request::RequestBase::Type::ADD_BUS_ROUTE) {
            const auto& request = dynamic_cast<const Request::AddBusRoute&>(*request_holder);
            request.Process(manager);
        } else if (type == Request::RequestBase::Type::READ_BUS_ROUTE) {
            const auto& request = dynamic_cast<const Request::ReadBusRouteInfo&>(*request_holder);
            responses.push_back(request.Process(manager));
        } else {
            throw runtime_error("unknown request type");
        }
    }
    return responses;
}

void PrintResponses(const ResponsesContainer& responses, ostream& stream = cout) {
    for (const auto& response : responses) {
        stream << response << endl;
    }
}

int main(int argc, const char** argv) {
#ifndef MASLO
    cout.precision(6);
#endif  // MASLO

    const auto requests = ReadRequests();
    const auto responses = ProcessRequests(requests);
    PrintResponses(responses);

    return 0;
}
