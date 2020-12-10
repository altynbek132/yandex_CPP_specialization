// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

#include <type_traits>

#include <numeric>
//#include <limits>

#include <cassert>

using namespace std;


template<typename Collection, class Sep>
string Join(const Collection &col, const Sep &sep);

// output reloads
#ifdef MASLO
// ========= Definitions
template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p);
template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v);
template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &);
template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup);
template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup);

// ========= Implementations

template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    return out << '[' << Join(v, ',') << ']';
}

template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
    return out << '{' << Join(m, ',') << '}';
}


template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup) {
    if (n != 0) {
        os << ", ";
    }
    os << std::get<n>(tup);
    print_tuple<n + 1>(os, tup);
}

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

#endif

template<typename Collection, class Sep>
string Join(const Collection &col, const Sep &sep) {
    stringstream ss;
    bool first = true;
    for (const auto &i : col) {
        if (!first) {
            ss << sep;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}


// utility functions
void txt() {
#ifdef MASLO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

void ensure(istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(ios::failbit);
        throw exception();
    }
    input.ignore(1);
}

void ensure(istream &input) {
    if (!input) {
        throw exception();
    }
}

void ensure(bool state) {
    if (!state) {
        throw exception();
    }
}

stringstream stream_line(istream &input) {
    string line;
    while (line.empty() && !input.eof()) {
        getline(input, line);
    }
    stringstream input_stream(line);
    return input_stream;
}

void io_files(ifstream &in, const string &input, ofstream &out, const string &output) {
    in = ifstream(input);
    out = ofstream(output);
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

template<class A, class B>
void AssertEqual(const A &actual, const B &expected, int line) {
    if (actual == expected) {
        return;
    }
    stringstream error;
    error << "Assertion error at line: " << line << endl;
    error << "Expected:" << endl << expected << endl;
    error << "Actual:" << endl << actual << endl;
    throw runtime_error(error.str());
}

template<class T>
void Assert(const T &t, int line) {
    AssertEqual(t, true, line);
}

class TestRunner {
 public:
  TestRunner(string description) : description(std::move(description)), fail_count(0) {}
  
  template<class Func>
  void RunTest(Func &test, string test_name) {
      try {
          test();
      } catch (exception &ex) {
          std::cerr << "test case \"" << test_name << "\" failed" << std::endl;
          std::cerr << ex.what() << std::endl;
          fail_count++;
      }
  }
  
  virtual ~TestRunner() {
      if (fail_count == 0) {
          std::cerr << "Block test \"" << description << "\" finished successfully!" << std::endl;
      } else {
          std::cerr << "Block test \"" << description << "\" finished with " << fail_count << " errors!" << std::endl;
          exit(1);
      }
  }
 
 private:
  string description;
  size_t fail_count;
};

void TestAll() {
    {
        TestRunner tr("basic test");
    }
}

// ==================================


enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

istream &operator>>(istream &is, QueryType &qt) {
    string command;
    is >> command;
    
    if (command == "NEW_BUS") {
        qt = QueryType::NewBus;
    } else if (command == "BUSES_FOR_STOP") {
        qt = QueryType::BusesForStop;
    } else if (command == "STOPS_FOR_BUS") {
        qt = QueryType::StopsForBus;
    } else if (command == "ALL_BUSES") {
        qt = QueryType::AllBuses;
    }
    return is;
}

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
    string bus, stop, query_type_string;
    
    is >> query_type_string;
    stringstream query_type_stream(query_type_string);
    query_type_stream >> q.type;
    switch (q.type) {
        case QueryType::NewBus : {
            std::size_t stop_count;
            is >> bus >> stop_count;
            vector<string> stops(stop_count);
            for (auto &stop_i : stops) {
                cin >> stop_i;
            }
            q = {q.type, bus, stop, stops};
            break;
        }
        case QueryType::BusesForStop : {
            is >> stop;
            q.stop = stop;
            break;
        }
        case QueryType::StopsForBus : {
            is >> bus;
            q.bus = bus;
            break;
        }
        case QueryType::AllBuses : {
            break;
        }
        default: {
            stringstream error;
            error << "invalid query type: " << query_type_string << endl;
            throw runtime_error(error.str());
            break;
        }
    }
    return is;
}

struct BusesForStopResponse {
  string stop;
  vs buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        os << Join(r.buses, ' ');
    }
    return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vs>> stop_with_buses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (r.stop_with_buses.empty()) {
        std::cout << "No bus";
        return os;
    }
    
    bool first = true;
    for (const auto &[stop, buses] : r.stop_with_buses) {
        if (!first) {
            os << endl;
        }
        first = false;
        
        os << "Stop " << stop << ": ";
        if (buses.size() == 1 && buses[0] == r.bus) {
            os << "no interchange";
            continue;
        }
        
        bool first_ = true;
        for (const auto &bus : buses) {
            if (bus == r.bus) {
                continue;
            }
            if (!first_) {
                os << ' ';
            }
            first_ = false;
            os << bus;
        }
    }
    return os;
}

struct AllBusesResponse {
  map<string, vs> bus_to_stops;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (r.bus_to_stops.empty()) {
        os << "No buses";
        return os;
    }
    bool first = true;
    for (auto &[bus, stops] : r.bus_to_stops) {
        if (!first) {
            os << endl;
        }
        first = false;
        os << "Bus " << bus << ": " << Join(stops, ' ');
    }
    return os;
}

class BusManager {
 public:
  void AddBus(const string &bus, const vector<string> &stops) {
      bus_to_stops[bus] = stops;
      for (auto &stop : stops) {
          stop_to_buses[stop].push_back(bus);
      }
  }
  
  BusesForStopResponse GetBusesForStop(const string &stop) const {
      if (stop_to_buses.count(stop) == 0) {
          return {stop, {}};
      }
      return {stop, stop_to_buses.at(stop)};
  }
  
  StopsForBusResponse GetStopsForBus(const string &bus) const {
      if (bus_to_stops.count(bus) == 0) {
          return {bus, {}};
      }
      
      vector<pair<string, vs>> stop_with_buses_response;
      for (auto &stop : bus_to_stops.at(bus)) {
          stop_with_buses_response.emplace_back(stop, stop_to_buses.at(stop));
      }
      return {bus, stop_with_buses_response};
  }
  
  AllBusesResponse GetAllBuses() const {
      return {bus_to_stops};
  }
 
 private:
  map<string, vs> bus_to_stops;
  map<string, vs> stop_to_buses;
};

int main() {
    txt();
    
    int query_count;
    Query q;
    
    cin >> query_count;
    
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:cout << bm.GetAllBuses() << endl;
                break;
        }
    }
    return 0;
}


// ==================================



//int main() {
//    txt();
//    ifstream in;
//    ofstream out;
//    io_files(in, "input.txt", out, "output.txt");
//    // ================================================================
//    TestAll();
//
//
//    return 0;
//}
