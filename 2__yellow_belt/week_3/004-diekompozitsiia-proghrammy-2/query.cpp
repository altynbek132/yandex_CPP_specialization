//
// Created by Addmin on 11.12.2020.
//

#include "query.h"

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
