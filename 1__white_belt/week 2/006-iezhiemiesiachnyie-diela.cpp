//
// Created by Addmin on 02.12.2020.
//

// #include <bits/stdc++.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pi;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

const vector<int> MONTH_LENGTHES = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
//    ADD i s
//    DUMP i
//    NEXT
    int CURRENT_MONTH = 0;
    vector<vector<string>> TASKS_OF_MONTH(MONTH_LENGTHES[CURRENT_MONTH]);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        string operation;
        cin >> operation;
        if (operation == "ADD") {
            int day_number;
            string task_name;
            cin >> day_number >> task_name;
            TASKS_OF_MONTH[--day_number].push_back(task_name);
        } else if (operation == "DUMP") {
            int day_number;
            cin >> day_number;
            auto &day = TASKS_OF_MONTH[--day_number];
            std::cout << day.size() << " ";
            for (auto &task : day) {
                std::cout << task << " ";
            }
            std::cout << std::endl;
        } else if (operation == "NEXT") {
            const int old_month_length = MONTH_LENGTHES[CURRENT_MONTH];
            CURRENT_MONTH = (CURRENT_MONTH + 1) % 12;
            const int new_month_length = MONTH_LENGTHES[CURRENT_MONTH];
            
            if (new_month_length < old_month_length) {
                auto &last_day = TASKS_OF_MONTH[new_month_length - 1];
                for (int i = new_month_length; i < old_month_length; ++i) {
                    auto &day = TASKS_OF_MONTH[i];
                    last_day.insert(last_day.end(), day.begin(), day.end());
                }
            }
            TASKS_OF_MONTH.resize(new_month_length);
        }
    }
    return 0;
}
