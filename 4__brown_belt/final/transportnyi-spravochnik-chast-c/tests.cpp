#include "tests.h"
#include "PresentationLayer.h"

using namespace std;

void test() {
    string input =
        "16\n"
        "Bus Looped_Single_Intrastop_Distance: A > B > C > A\n"
        "Stop A: 55.574371, 37.6517, 100m to B\n"
        "Stop B: 55.581065, 37.64839, 200m to C\n"
        "Stop C: 55.587655, 37.645687, 300m to A\n"

        "Bus Looped_Double_Intrastop_Distance: D > E > F > D\n"
        "Stop D: 55.574371, 37.6517, 100m to E, 400m to F\n"
        "Stop E: 55.581065, 37.64839, 200m to F, 500m to D\n"
        "Stop F: 55.587655, 37.645687, 300m to D, 600m to E\n"

        "Bus Straight_Single_Intrastop_Distance: G - H - I\n"
        "Stop G: 55.574371, 37.6517, 100m to H\n"
        "Stop H: 55.581065, 37.64839, 200m to I\n"
        "Stop I: 55.587655, 37.645687, 300m to H\n"

        "Bus Straight_Double_Intrastop_Distance: J - K - L\n"
        "Stop J: 55.574371, 37.6517, 100m to K, 400m to L\n"
        "Stop K: 55.581065, 37.64839, 200m to L, 500m to J\n"
        "Stop L: 55.587655, 37.645687, 300m to J, 600m to K\n";

    string query =
        "5\n"
        "Bus Looped_Single_Intrastop_Distance\n"
        "Bus Looped_Double_Intrastop_Distance\n"
        "Bus Straight_Single_Intrastop_Distance\n"
        "Bus Straight_Double_Intrastop_Distance";

    stringstream input_stream_modify(input);
    stringstream input_stream_read(query);
    auto modify_requests = ReadRequests(input_stream_modify);
    auto read_requests = ReadRequests(input_stream_read);
    vector<unique_ptr<Request::Base>> all_requests;
    all_requests.reserve(modify_requests.size() + read_requests.size());
    all_requests.insert(all_requests.end(), make_move_iterator(modify_requests.begin()),
                        make_move_iterator(modify_requests.end()));
    all_requests.insert(all_requests.end(), make_move_iterator(read_requests.begin()),
                        make_move_iterator(read_requests.end()));

    BusManager manager;
    const auto responses = ProcessRequests(all_requests, manager);
    stringstream ss_o;
    PrintResponses(responses, ss_o);

    auto expected =
        "Bus Looped_Single_Intrastop_Distance: 4 stops on route, 3 unique stops, 600 route length, "
        "0.196736 curvature\n"
        "Bus Looped_Double_Intrastop_Distance: 4 stops on route, 3 unique stops, 600 route length, "
        "0.196736 curvature\n"
        "Bus Straight_Single_Intrastop_Distance: 5 stops on route, 3 unique stops, 700 route "
        "length, 0.229497 curvature\n"
        "Bus Straight_Double_Intrastop_Distance: 5 stops on route, 3 unique stops, 1400 route "
        "length, 0.458993 curvature\n";
    auto actual = ss_o.str();

    ofstream test_expected_out_file("test_expected_out_file.txt");
    test_expected_out_file << expected << endl;

    ofstream test_actual_out_file("test_actual_out_file.txt");
    test_actual_out_file << actual << endl;
    ASSERT_EQUAL(actual, expected);
}
