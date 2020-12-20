#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <set>

using namespace std;


class Stats {
 public:
  Stats();
  void Init();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int> &GetMethodStats() const;
  const map<string_view, int> &GetUriStats() const;
  
  static const set<string> Methods;
  static const set<string> Uris;
 private:
  map<string_view, int> method_to_count_;
  map<string_view, int> uri_to_count_;
};

HttpRequest ParseRequest(string_view line);

