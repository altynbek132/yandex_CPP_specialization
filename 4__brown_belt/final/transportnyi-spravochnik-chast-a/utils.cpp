#include "utils.h"

using namespace std;

template <typename It>
Range<It>::Range(It begin, It end) : begin_(begin), end_(end) {}
template <typename It>
It Range<It>::begin() const {
    return begin_;
}
template <typename It>
It Range<It>::end() const {
    return end_;
}
pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter) {
    const size_t pos = s.find(delimiter);
    if (pos == s.npos) {
        return {s, nullopt};
    } else {
        return {s.substr(0, pos), s.substr(pos + delimiter.length())};
    }
}
pair<string_view, string_view> SplitTwo(string_view s, string_view delimiter) {
    const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    return {lhs, rhs_opt.value_or("")};
}
string_view ReadToken(string_view& s, string_view delimiter) {
    const auto [lhs, rhs] = SplitTwo(s, delimiter);
    s = rhs;
    return lhs;
}
int ConvertToInt(string_view str) {
    // use std::from_chars when available to git rid of string copy
    size_t pos;
    const int result = stoi(string(str), &pos);
    if (pos != str.length()) {
        std::stringstream error;
        error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
        throw invalid_argument(error.str());
    }
    return result;
}
double ConvertToDouble(std::string_view str) {
    size_t pos;
    const double result = stod(str.data(), &pos);
    if (pos != str.length()) {
        std::stringstream error;
        error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
        throw invalid_argument(error.str());
    }
    return result;
}

size_t pow_size_t(size_t x, size_t p) {
    if (p == 0)
        return 1;
    if (p == 1)
        return x;

    size_t tmp = pow_size_t(x, p / 2);
    if (p % 2 == 0)
        return tmp * tmp;
    else
        return x * tmp * tmp;
}

size_t PolynomicCombine(size_t x, const vector<size_t>& v) {
    size_t res = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        res += pow_size_t(x, v.size() - 1 - i) * v[i];
    }
    return res;
}
void TrimLeft(string_view& s) {
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
}
void TrimRight(string_view& s) {
    while (!s.empty() && isspace(s.back())) {
        s.remove_suffix(1);
    }
}
void Trim(string_view& s) {
    TrimLeft(s);
    TrimRight(s);
}
template <typename Number>
Number ReadNumberOnLine(istream& stream) {
    Number number;
    stream >> number;
    std::string dummy;
    getline(stream, dummy);
    return number;
}
