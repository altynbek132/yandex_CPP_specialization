// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

#include <type_traits>

#include <numeric>
//#include <limits>

#include <cassert>
#include <random>

using namespace std;


// ========= Definitions
template<typename Collection>
string Join(const Collection &col, char sep);

// output reloads
#ifdef MASLO
template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p);
template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v);
template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m);

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &);
template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup);
template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup);

// ========= Implementations

template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    return out << '[' << Join(v, ',') << ']';
}

template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
    return out << '{' << Join(m, ',') << '}';
}


template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup) {
    if (n != 0) {
        os << ", ";
    }
    os << std::get<n>(tup);
    print_tuple<n + 1>(os, tup);
}

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

#endif

template<typename Collection>
string Join(const Collection &col, char sep) {
    stringstream ss;
    bool first = true;
    for (const auto &i : col) {
        if (!first) {
            ss << sep;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}


// utility functions
void txt() {
#ifdef MASLO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

void ensure(istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(ios::failbit);
        throw exception();
    }
    input.ignore(1);
}

void ensure(istream &input) {
    if (!input) {
        throw exception();
    }
}

void ensure(bool state) {
    if (!state) {
        throw exception();
    }
}

stringstream stream_line(istream &input) {
    string line;
    while (line.empty() && !input.eof()) {
        getline(input, line);
    }
    stringstream input_stream(line);
    return input_stream;
}

void io_files(ifstream &in, const string &input, ofstream &out, const string &output) {
    in = ifstream(input);
    out = ofstream(output);
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

template<class A, class B>
void _AssertEqual(const A &actual, const B &expected, const string &file, int line) {
    if (actual == expected) {
        return;
    }
    
    ifstream in(file);
    int line_ = line;
    while (--line_) {
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    string error_line;
    getline(in, error_line);
    in.close();
    
    stringstream error;
    error << "Assertion error at line " << line << ": " << endl;
    error << error_line << endl;
    error << "Expected:" << endl << expected << endl;
    error << "Actual:" << endl << actual << endl;
    throw runtime_error(error.str());
}

#define AssertEqual(actual, expected)       _AssertEqual(actual, expected, __FILE__, __LINE__)

void _Assert(const bool &statement, const string &file, int line) {
    _AssertEqual(statement, true, file, line);
}

#define Assert(statement)       _Assert(statement, __FILE__, __LINE__)


class TestRunner {
 public:
  TestRunner(string description) : description(std::move(description)), fail_count(0) {}
  
  template<class Func>
  void RunTest(Func &test, const string &test_name) {
      try {
          test();
      } catch (exception &ex) {
          std::cerr << "test case \"" << test_name << "\" failed" << std::endl;
          std::cerr << ex.what() << std::endl;
          fail_count++;
      } catch (...) {
          std::cerr << "Unknown exception caught" << endl;
          fail_count++;
      }
  }
  
  virtual ~TestRunner() {
      if (fail_count == 0) {
          std::cerr << "Block test \"" << description << "\" finished successfully!" << std::endl;
      } else {
          std::cerr << "Block test \"" << description << "\" finished with " << fail_count << " errors!" << std::endl;
          exit(1);
      }
  }
 
 private:
  string description;
  size_t fail_count;
};

// ==================================
#ifdef MASLO

class Rational {
 public:
  Rational();
  Rational(int numerator, int denominator);
  
  int Numerator() const;
  int Denominator() const;
};

#endif

void basic_test() {
    mt19937 gen;
    uniform_int_distribution<int> unif(-1000, 1000);
    for (size_t i = 0; i < 100; ++i) {
        int numer, denom;
        do {
            numer = unif(gen), denom = unif(gen);
        } while (numer == 0 || denom == 0);
        
        Rational r(numer, denom);
        
        int fraction = gcd(abs(numer), abs(denom));
        numer /= fraction;
        denom /= fraction;
        if (denom < 0) {
            numer *= -1;
            denom *= -1;
        }
        if (numer == 0) {
            denom = 1;
        }
        
        AssertEqual(r.Numerator(), numer);
        AssertEqual(r.Denominator(), denom);
    }
}

void default_constructor_test() {
    Rational r;
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);
}

void positive_denom() {
    {
        Rational r(-1, 1);
        AssertEqual(r.Numerator(), -1);
        AssertEqual(r.Denominator(), 1);
    }
    {
        Rational r(1, -1);
        AssertEqual(r.Numerator(), -1);
        AssertEqual(r.Denominator(), 1);
    }
}

void positive_test() {
    Rational r(-1, -2);
    AssertEqual(r.Numerator(), 1);
    AssertEqual(r.Denominator(), 2);
}

void denom_one() {
    Rational r(0, 228);
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);
}

void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "should reduce fraction");
        tr.RunTest(default_constructor_test, "default constructor");
        tr.RunTest(positive_denom, "negative rational should have negative numerator");
        tr.RunTest(positive_test, "positive rational should have both positive numerator and denominator");
        tr.RunTest(denom_one, "if numerator is zero denominator should be 1");
    }
}

// ==================================

int main() {
    txt();
    ifstream in;
    ofstream out;
    io_files(in, "input.txt", out, "output.txt");
    // ================================================================
    TestAll();
    
    
    return 0;
}
