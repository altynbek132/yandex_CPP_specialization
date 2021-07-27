#include <bits/stdc++.h>
#include "PresentationLayer.h"
#include "Request.h"
#include "json.h"
#include "profile.h"
#include "test_runner.h"
#include "tests.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, true, false);

#endif  // MASLO

using namespace std;

int main(int argc, const char** argv) {
#ifndef MASLO
    cout.precision(6);
#endif  // MASLO
    const auto& root = Json::Load(cin).GetRoot().AsMap();
    auto modify_requests = ReadRequests(root.at("base_requests").AsArray(), Request::OperationType::MODIFY);
    auto read_requests = ReadRequests(root.at("stat_requests").AsArray(), Request::OperationType::READ);
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

    BusManager manager;
    const auto responses = ProcessRequests(all_requests, manager);
    PrintResponses(responses);

    return 0;
}
