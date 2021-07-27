#pragma once
#include <bits/stdc++.h>
#include "Request.h"
#include "Response.h"
#include "profile.h"
#include "test_runner.h"
#include "utils.h"

Request::Holder ParseRequest(std::string_view str);

std::vector<Request::Holder> ReadRequests(std::istream& input = cin);

using ResponsesContainer = std::vector<Response::Holder>;
ResponsesContainer ProcessRequests(const std::vector<Request::Holder>& requests, BusManager& manager);

void PrintResponses(const ResponsesContainer& responses, std::ostream& stream = cout);
