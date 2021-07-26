#include <bits/stdc++.h>
#include "PresentationLayer.h"
#include "profile.h"
#include "test_runner.h"
#include "utils.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, true, false);

#endif  // MASLO

using namespace std;

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

    BusManager manager;
    const auto responses = ProcessRequests(all_requests, manager);
    PrintResponses(responses);

    return 0;
}
