#pragma once

#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

namespace Json {

class Node : std::variant<std::vector<Node>, std::map<std::string, Node>, int, double, std::string, bool> {
   public:
    using variant::variant;

    const auto& AsArray() const { return std::get<std::vector<Node>>(*this); }
    const auto& AsMap() const { return std::get<std::map<std::string, Node>>(*this); }
    int AsInt() const { return std::get<int>(*this); }
    double AsDouble() const { return std::get<double>(*this); }
    const auto& AsString() const { return std::get<std::string>(*this); }
    const auto& AsBool() const { return std::get<bool>(*this); }
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

class Document {
   public:
    explicit Document(Node root);

    const Node& GetRoot() const;

    friend std::ostream& operator<<(std::ostream& os, const Document& document);

   private:
    Node root;
};

Document Load(std::istream& input);

}  // namespace Json
