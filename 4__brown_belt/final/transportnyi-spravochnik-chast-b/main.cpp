#include <bits/stdc++.h>
#include "Request.h"
#include "Response.h"
#include "profile.h"
#include "test_runner.h"
#include "utils.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

using namespace std;

Request::Holder ParseRequest(string_view str) {
    using namespace Request;

    auto [lhs, rhs] = SplitTwoStrict(str, ":");
    const OperationType operation_type = rhs ? OperationType::MODIFY : OperationType::READ;

    auto request_type = ConvertRequestTypeFromString(ReadToken(lhs), operation_type);
    if (!request_type) {
        return nullptr;
    }
    auto request = Base::Create(*request_type);
    if (request) {
        request->ParseFrom(str);
    }
    return request;
}

vector<Request::Holder> ReadRequests(istream& input = cin) {
    auto request_count = ReadNumberOnLine<size_t>(input);
    vector<Request::Holder> requests;
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

using ResponsesContainer = vector<Response::Holder>;
ResponsesContainer ProcessRequests(const vector<Request::Holder>& requests) {
    ResponsesContainer responses;
    BusManager manager;

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

void PrintResponses(const ResponsesContainer& responses, ostream& stream = cout) {
    for (const auto& response : responses) {
        stream << *response << endl;
    }
}

int main(int argc, const char** argv) {
#ifndef MASLO
    cout.precision(6);
#endif  // MASLO

    auto modify_requests = ReadRequests();
    auto read_requests = ReadRequests();
    vector<unique_ptr<Request::Base>> all_requests;
    all_requests.reserve(modify_requests.size() + read_requests.size());
    all_requests.insert(all_requests.end(), make_move_iterator(modify_requests.begin()),
                        make_move_iterator(modify_requests.end()));
    all_requests.insert(all_requests.end(), make_move_iterator(read_requests.begin()),
                        make_move_iterator(read_requests.end()));

#ifdef MASLO
    for (auto& request : all_requests) {
        std::cout << *request << std::endl;
    }
    std::cout << "====\n\n\n" << std::endl;
#endif  // MASLO

    const auto responses = ProcessRequests(all_requests);
    PrintResponses(responses);

    return 0;
}
