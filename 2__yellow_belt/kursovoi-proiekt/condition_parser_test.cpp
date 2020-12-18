#ifdef MASLO
#include "condition_parser.h"
#include "unit_test_framework.h"

#include <sstream>

using namespace std;

void TestParseCondition() {
    {
        istringstream is("date != 2017-11-18");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""));
        Assert(!root->Evaluate({2017, 11, 18}, ""));
    }
    {
        istringstream is(R"(event == "sport event")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "sport event"));
        Assert(!root->Evaluate({2017, 1, 1}, "holiday"));
    }
    {
        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""));
        Assert(root->Evaluate({2017, 3, 1}, ""));
        Assert(root->Evaluate({2017, 6, 30}, ""));
        Assert(!root->Evaluate({2017, 7, 1}, ""));
        Assert(!root->Evaluate({2016, 12, 31}, ""));
    }
    {
        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"));
        Assert(!root->Evaluate({2017, 1, 1}, "sport event"));
        Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"));
    }
    {
        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2017, 11, 18}, "holiday"));
        Assert(!root->Evaluate({2017, 11, 18}, "work day"));
        Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"));
    }
    {
        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"));
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"));
    }
    {
        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2016, 1, 1}, "holiday"));
        Assert(root->Evaluate({2017, 1, 2}, "holiday"));
        Assert(root->Evaluate({2017, 1, 2}, "workday"));
        Assert(!root->Evaluate({2018, 1, 2}, "workday"));
    }
    {
        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2016, 1, 1}, "event"));
        Assert(root->Evaluate({2017, 1, 2}, "holiday"));
        Assert(root->Evaluate({2017, 1, 2}, "workday"));
        Assert(!root->Evaluate({2018, 1, 2}, "workday"));
    }
    {
        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"));
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"));
    }
    {
        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({1, 1, 1}, "2017-01-01"));
        Assert(!root->Evaluate({2016, 1, 1}, "event"));
        Assert(root->Evaluate({2016, 1, 2}, "event"));
    }
}

#endif
