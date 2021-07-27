#pragma once

#include <bits/stdc++.h>

template <typename It>
class Range {
   public:
    Range(It begin, It end);
    It begin() const;
    It end() const;

   private:
    It begin_;
    It end_;
};
std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s,
                                                                            std::string_view delimiter = " ");
std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");
template <typename Pred>
std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s,
                                                                            Pred predicate);
template <typename Pred>
std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, Pred predicate);
std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");
template <typename Pred>
std::string_view ReadTokenWhile(std::string_view& s, Pred);
std::string_view ReadToken(std::string_view& s, size_t count);
char ReadChar(std::string_view& s);
void TrimLeft(std::string_view& s);
void TrimRight(std::string_view& s);
void Trim(std::string_view& s);
int ConvertToInt(std::string_view str);
double ConvertToDouble(std::string_view str);
size_t PolynomicCombine(size_t x, const std::vector<size_t>& v);
template <typename Number>
Number ReadNumberOnLine(std::istream& stream);

template <typename Number>
Number ReadNumberOnLine(std::istream& stream) {
    Number number;
    stream >> number;
    std::string dummy;
    getline(stream, dummy);
    return number;
}

/* ========================================================
template definitions
======================================================== */

template <typename Pred>
std::string_view ReadTokenWhile(std::string_view& s, Pred predicate) {
    const auto [lhs, rhs] = SplitTwo(s, predicate);
    s = rhs;
    return lhs;
}

template <typename Pred>
std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s,
                                                                            Pred predicate) {
    using namespace std;
    auto it = find_if(s.begin(), s.end(), predicate);
    if (it == s.end()) {
        return {s, nullopt};
    }
    auto pos = s.begin() - it;
    return {s.substr(0, pos), s.substr(pos + 1)};
}

template <typename Pred>
std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, Pred predicate) {
    const auto [lhs, rhs_opt] = SplitTwoStrict(s, predicate);
    return {lhs, rhs_opt.value_or("")};
}
