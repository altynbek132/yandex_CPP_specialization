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
std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");
void TrimLeft(std::string_view& s);
void TrimRight(std::string_view& s);
void Trim(std::string_view& s);
int ConvertToInt(std::string_view str);
double ConvertToDouble(std::string_view str);
size_t PolynomicCombine(size_t x, const std::vector<size_t>& v);
template <typename Number>
Number ReadNumberOnLine(std::istream& stream);
