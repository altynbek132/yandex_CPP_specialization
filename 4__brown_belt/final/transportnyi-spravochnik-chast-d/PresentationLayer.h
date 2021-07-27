#pragma once
#include <bits/stdc++.h>
#include "Request.h"
#include "Response.h"
#include "json.h"
#include "profile.h"
#include "utils.h"

Request::Holder ConvertJsonToRequest(const Json::Node&, Request::OperationType);

std::vector<Request::Holder> ReadRequests(const std::vector<Json::Node>&, Request::OperationType);

using ResponsesContainer = std::vector<Response::Holder>;
ResponsesContainer ProcessRequests(const std::vector<Request::Holder>& requests, BusManager& manager);

void PrintResponses(const ResponsesContainer& responses, std::ostream& stream = cout);
