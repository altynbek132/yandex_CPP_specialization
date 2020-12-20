//
// Created by Addmin on 20.12.2020.
//

#include "stats.h"
#include <vector>
#include <utility>

const string UNKNOWN = "UNKNOWN";
const string unknown = "unknown";

const set<string> Stats::Methods = {
    "GET",
    "POST",
    "PUT",
    "DELETE",
    UNKNOWN
};

const set<string> Stats::Uris = {
    "/",
    "/order",
    "/product",
    "/basket",
    "/help",
    unknown
};


void Stats::AddMethod(string_view method) {
    if (Methods.count(string(method)) != 0) {
        method_to_count_[method]++;
    } else {
        method_to_count_[UNKNOWN]++;
    }
}

void Stats::AddUri(string_view uri) {
    if (Uris.count(string(uri)) != 0) {
        uri_to_count_[uri]++;
    } else {
        uri_to_count_[unknown]++;
    }
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return method_to_count_;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return uri_to_count_;
}

Stats::Stats() {
    Init();
}

void Stats::Init() {
    for (const auto &req : Methods) {
        method_to_count_[req] = 0;
    }
    for (const auto &req : Uris) {
        uri_to_count_[req] = 0;
    }
}

//

set<string> Protocols_cache = {
    "HTTP/1.1"
};

set<string> Methods_cache = Stats::Methods;

set<string> Uris_cache = Stats::Uris;

void skip_spaces(string_view &str_v) {
    std::size_t i = 0;
    for (; i < str_v.size(); ++i) {
        if (str_v[i] != ' ') { break; }
    }
    str_v.remove_prefix(i);
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest req;
    size_t end;
    
    vector<pair<string_view &, set<string> &>> v
        = {{req.method, Methods_cache}, {req.uri, Uris_cache}, {req.protocol, Protocols_cache}};
    
    for (auto p : v) {
        skip_spaces(line);
        
        auto&[req_prop, saved_set] = p;
        end = line.find(' ');
        
        string req_s = string(line.substr(0, end));
        string_view req_v;
        auto it = saved_set.find(req_s);
        if (it == saved_set.end()) {
            req_v = *(saved_set.insert(req_s).first);
        } else {
            req_v = *it;
        }
        req_prop = req_v;
        
        if (end == std::string_view::npos) { break; }
        line.remove_prefix(end + 1);
    }
    
    return req;
}
