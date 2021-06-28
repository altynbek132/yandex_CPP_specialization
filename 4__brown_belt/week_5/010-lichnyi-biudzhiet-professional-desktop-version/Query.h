#include <istream>
#include <memory>
#include <ostream>

#include "Date.h"
#pragma once

namespace Query {

enum class Type {
    Earn,
    ComputeIncome,
    PayTax,
    Spend,
};

// todo: incorrect implementation
class Query {
   public:
    Query(const Date::Date& from, const Date::Date& to);
    Query(const Date::Date& from, const Date::Date& to, double value);
    virtual Type type() const = 0;
    Date::Date from, to;
    double value;
};

class Earn : public Query {
    using Query::Query;

   public:
    Type type() const override { return Type::Earn; }
};
class ComputeIncome : public Query {
    using Query::Query;

   public:
    Type type() const override { return Type::ComputeIncome; }
};
class PayTax : public Query {
    using Query::Query;

   public:
    Type type() const override { return Type::PayTax; }
};
class Spend : public Query {
    using Query::Query;

   public:
    Type type() const override { return Type::Spend; }
};

std::shared_ptr<Query> Read(std::istream& is);

class UnknownQueryError : public std::exception {
   private:
    std::string message_;

   public:
    explicit UnknownQueryError(std::string message);
    const char* what() const noexcept override;
};

}  // namespace Query
