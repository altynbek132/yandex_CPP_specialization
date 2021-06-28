#include <bits/stdc++.h>
#include "BudgetManager.h"
#include "Query.h"
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

vector<shared_ptr<Query::Query>> ReadQueries(istream& is = cin) {
    size_t Q;
    cin >> Q;
    cin.ignore();
    vector<shared_ptr<Query::Query>> res;
    while (Q--) {
        res.push_back(Query::Read(is));
    }
    return res;
}

ostream& ExecuteQueries(vector<shared_ptr<Query::Query>> queries, ostream& os = cout) {
    BudgetManager::Manager bm;
    for (auto& query : queries) {
        switch (query->type()) {
            case Query::Type::Earn: {
                bm.Earn(query->from, query->to, query->value);
                break;
            }
            case Query::Type::ComputeIncome: {
                os << bm.ComputeIncome(query->from, query->to) << endl;
                break;
            }
            case Query::Type::PayTax: {
                bm.PayTax(query->from, query->to);
                break;
            }
            default:
                throw runtime_error("chotam?");
        }

#ifdef MASLO1
        std::cout << bm << std::endl << std::endl;
#endif  // MASLO
    }

    return os;
}

int main(int argc, const char** argv) {
#ifndef MASLO
    cout.precision(25);
#endif  // MASLO

    ExecuteQueries(ReadQueries());

    return 0;
}
