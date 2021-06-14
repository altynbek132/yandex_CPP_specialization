#include <readFromInputTxt.h>
#pragma once

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& s) {
    os << "[";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "]";
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::deque<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
template <class K, class V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
    if (!(t == u)) {
        //    if (!((T) t == (T) u)) {
        std::ostringstream os;
        os << "Assertion failed: \n" << t << " != \n" << u;
        if (!hint.empty()) {
            os << "\nhint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
   public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

   private:
    int fail_count = 0;
};

#define ASSERT_EQUAL(x, y)                                                \
    {                                                                     \
        stringstream __assert_equal_private_os;                           \
        __assert_equal_private_os << #x << " != " << #y << ", " << endl   \
                                  << __FILE__ << ":" << __LINE__ << endl; \
        AssertEqual(x, y, __assert_equal_private_os.str());               \
    }

#define ASSERT(x)                                                                                        \
    {                                                                                                    \
        stringstream __assert_equal_private_os;                                                          \
        __assert_equal_private_os << #x << " is false, " << endl << __FILE__ << ":" << __LINE__ << endl; \
        Assert(x, __assert_equal_private_os.str());                                                      \
    }

#define RUN_TEST(tr, func) tr.RunTest(func, #func)
