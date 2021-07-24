#pragma once
#include <bits/stdc++.h>
#include <ostream>

using namespace std;

namespace Response {

struct Base;

using Holder = shared_ptr<Base>;

struct Base {
    virtual void print(std::ostream& os) const = 0;
};
ostream& operator<<(ostream& out, const Base& response) {
    response.print(out);
    return out;
}


//
struct BusRouteFound : Base {
    string_view bus_name;
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
    void print(ostream& os) const override;
};
struct BusRouteNotFound : Base {
    string_view bus_name;
    void print(ostream& os) const override;
};

}  // namespace Response
