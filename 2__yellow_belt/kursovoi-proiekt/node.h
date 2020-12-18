//
// Created by Addmin on 15.12.2020.
//

#pragma once
#include <memory>
#include "date.h"
#include "comparison.h"
#include "logical_op.h"
#include <string>


class Node {
 public:
  virtual bool Evaluate(const Date &date, const std::string &event) = 0;
 private:
};

class EmptyNode : public Node {
 public:
  bool Evaluate(const Date &date, const std::string &event) override;
 
 private:
};

class DateComparisonNode : public Node {
 public:
  DateComparisonNode(Comparison cmp, const Date &date);
  bool Evaluate(const Date &date, const std::string &event) override;
 
 private:
  Comparison cmp;
  Date date;
};

class EventComparisonNode : public Node {
 public:
  EventComparisonNode(Comparison cmp, std::string event);
  bool Evaluate(const Date &date, const std::string &event) override;
 
 private:
  Comparison cmp;
  std::string event;
};


class LogicalOperationNode : public Node {
 public:
  LogicalOperationNode(LogicalOperation logical_operation,
                       std::shared_ptr<Node> left,
                       std::shared_ptr<Node> right);
  bool Evaluate(const Date &date, const std::string &event) override;
 
 private:
  LogicalOperation logical_operation_;
  std::shared_ptr<Node> left, right;
};
