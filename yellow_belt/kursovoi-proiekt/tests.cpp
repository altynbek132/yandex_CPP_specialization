#ifdef MASLO

#include "tests.h"
#include "condition_parser.h"
//#include <bits/stdc++.h>
#include <random>

using namespace std;

string gen_random(const int len) {
    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    tmp_s.reserve(len);
    
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

string ParseEvent(istream &is);
void TestParseCondition();

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        vector<string> v = {"first event  ", "second event"};
        AssertEqual(events, v);
    }
}




void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> dd(-10, 10);
    std::uniform_int_distribution<int> ii(-10, 10);
}

// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
        tr.RunTest(TestParseEvent, "TestParseEvent");
        tr.RunTest(TestParseCondition, "TestParseCondition");
    }
}

#endif
