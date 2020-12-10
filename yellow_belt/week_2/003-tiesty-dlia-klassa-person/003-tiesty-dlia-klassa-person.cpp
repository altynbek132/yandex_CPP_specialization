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

class Person {
 public:
  void ChangeFirstName(int year, const string &first_name) {
      // добавить факт изменения имени на first_name в год year
      _year_to_first_name[year] = first_name;
  }
  
  void ChangeLastName(int year, const string &last_name) {
      // добавить факт изменения фамилии на last_name в год year
      _year_to_last_name[year] = last_name;
  }
  
  string GetFullName(int year) {
      // получить имя и фамилию по состоянию на конец года year
      string first = find_closest(year, _year_to_first_name);
      string last = find_closest(year, _year_to_last_name);
      if (first.empty() && last.empty()) {
          return "Incognito";
      }
      if (first.empty()) {
          return last + " with unknown first name";
      }
      if (last.empty()) {
          return first + " with unknown last name";
      }
      return first + " " + last;
  }
 
 private:
  // приватные поля
  map<int, string> _year_to_first_name;
  map<int, string> _year_to_last_name;
  
  string find_closest(int year_, const map<int, string> &m_) {
      string closest;
      for (auto &[year, value] : m_) {
          if (year > year_) { break; }
          closest = value;
      }
      return closest;
  }
};

#endif


using Change = pair<int, string>;

pair<vector<pair<Change, Change>>, vector<pair<Change, Change>>>
gen_changes(int first_decade, int last_decade) {
    vector<pair<Change, Change>> changes;
    for (int decade = first_decade; decade <= last_decade; decade++) {
        int year = decade * 10;
        string first, last;
        first = to_string(year) + "_first";
        last = to_string(year + 5) + "_last";
        changes.push_back({{year, first}, {year + 5, last}});
    }
    auto changes_shuffled = changes;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(changes_shuffled.begin(), changes_shuffled.end(), g);
    return {changes, changes_shuffled};
}

void apply_changes(Person &p, const vector<pair<Change, Change>> &changes) {
//    for (auto &[first_name_change, last_name_change] : changes) {
    for (auto &pp : changes) {
        auto &first_name_change = pp.first;
        auto &last_name_change = pp.second;
        {
//            auto&[year, first] = first_name_change;
//            p.ChangeFirstName(year, first);
            p.ChangeFirstName(first_name_change.first, first_name_change.second);
        }
        {
//            auto&[year, last] = last_name_change;
//            p.ChangeLastName(year, last);
            p.ChangeLastName(last_name_change.first, last_name_change.second);
        }
    }
}

template<class Func>
void check_change(Person &p, const Change &current, const Change &next, Func get_name) {
//    auto&[year_current, name_current] = current;
    auto &year_current = current.first;
    auto &name_current = current.second;
//    auto&[year_next, name_next] = next;
    auto &year_next = next.first;
//    auto &name_next = next.second;
    
    for (int year = year_current; year < year_next; ++year) {
        stringstream name_stream(p.GetFullName(year));
        string actual_name;
        get_name(name_stream, actual_name);
        AssertEqual(actual_name, name_current);
    }
}

void check_changes(Person &p, const vector<pair<Change, Change>> &changes) {
    for (size_t i = 1; i < changes.size() - 1; ++i) {
//        auto&[first_name_change_current, last_name_change_current] = changes[i];
        auto &first_name_change_current = changes[i].first;
        auto &last_name_change_current = changes[i].second;
//        auto&[first_name_change_next, last_name_change_next] = changes[i + 1];
        auto &first_name_change_next = changes[i + 1].first;
        auto &last_name_change_next = changes[i + 1].second;
        
        check_change(p,
                     first_name_change_current,
                     first_name_change_next,
                     [](istream &is, string &name) {
                       is >> name;
                     });
        check_change(p,
                     last_name_change_current,
                     last_name_change_next,
                     [](istream &is, string &name) {
                       is.ignore(numeric_limits<streamsize>::max(), ' ');
                       is >> name;
                     });
    }
}

void basic_test() {
//    const auto[changes, changes_shuffled] = gen_changes(-5, 6);
    const auto p_changes = gen_changes(-5, 6);
    auto &changes = p_changes.first;
    auto &changes_shuffled = p_changes.second;
    Person p;
    apply_changes(p, changes_shuffled);
    check_changes(p, changes);
}

void ignore_double_change_test() {
//    const auto[changes, changes_shuffled] = gen_changes(-5, 6);
    const auto p_changes = gen_changes(-5, 6);
    auto &changes = p_changes.first;
    auto &changes_shuffled = p_changes.second;
    Person p;
    apply_changes(p, changes_shuffled);
    apply_changes(p, changes);
    check_changes(p, changes);
}

void incognito_test() {
//    const auto[changes, changes_shuffled] = gen_changes(-5, 6);
    const auto p_changes = gen_changes(-5, 6);
    auto &changes = p_changes.first;
    auto &changes_shuffled = p_changes.second;
    Person p;
    AssertEqual(p.GetFullName(228 - 1488), "Incognito");
    apply_changes(p, changes_shuffled);
    check_changes(p, changes);
    AssertEqual(p.GetFullName(228 - 1488), "Incognito");
}

void first_name_test() {
    Person p;
    p.ChangeFirstName(228, "Valeriy");
    AssertEqual(p.GetFullName(228 + 228), "Valeriy with unknown last name");
    
    p.ChangeLastName(1488, "Zhmyshenko");
    AssertEqual(p.GetFullName(228 + 228), "Valeriy with unknown last name");
}

void last_name_test() {
    Person p;
    p.ChangeLastName(228, "Zhmyshenko");
    AssertEqual(p.GetFullName(228 + 228), "Zhmyshenko with unknown first name");
    
    p.ChangeFirstName(1488, "Valeriy");
    AssertEqual(p.GetFullName(228 + 228), "Zhmyshenko with unknown first name");
}

void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
        tr.RunTest(ignore_double_change_test, "ignore change on same year");
        tr.RunTest(incognito_test, "getfullname: incognito");
        tr.RunTest(first_name_test, "getfullname: without first name");
        tr.RunTest(last_name_test, "getfullname: without last name");
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
