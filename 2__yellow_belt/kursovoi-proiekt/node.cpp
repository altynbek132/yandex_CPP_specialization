//
// Created by Addmin on 15.12.2020.
//

#include "node.h"

#include <utility>

EventComparisonNode::EventComparisonNode(Comparison cmp, std::string event) : cmp(cmp), event(std::move(event)) {}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date &date) : cmp(cmp), date(date) {}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logical_operation,
                                           std::shared_ptr<Node> left,
                                           std::shared_ptr<Node> right)
    : logical_operation_(logical_operation), left(std::move(left)), right(std::move(right)) {}


bool EmptyNode::Evaluate(const Date &date, const std::string &event) {
    return true;
}

bool EventComparisonNode::Evaluate(const Date &date_, const std::string &event_) {
    return PerformComparison(cmp, event_, event);
}

bool DateComparisonNode::Evaluate(const Date &date_, const std::string &event_) {
    return PerformComparison(cmp, date_, date);
}

bool LogicalOperationNode::Evaluate(const Date &date_, const std::string &event_) {
    return PerformLogicalOperation(logical_operation_, left->Evaluate(date_, event_), right->Evaluate(date_, event_));
}
