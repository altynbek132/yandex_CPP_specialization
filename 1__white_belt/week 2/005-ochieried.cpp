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


int main() {
    vector<bool> q;
    int Q;
    cin>>Q;
    for (int i = 0; i < Q; ++i) {
//        WORRY i: пометить i-го человека с начала очереди как беспокоящегося;
//        QUIET i: пометить i-го человека как успокоившегося;
//        COME k: добавить k спокойных человек в конец очереди;
//        COME -k: убрать k человек из конца очереди;
//        WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
        string action;
        cin >> action;
        if (action == "WORRY") {
            int i;
            cin >> i;
            q[i] = true;
        } else if (action == "QUIET") {
            int i;
            cin >> i;
            q[i] = false;
        } else if (action == "COME") {
            int k;
            cin >> k;
            k += q.size();
            q.resize(k, false);
        } else if (action == "WORRY_COUNT") {
            std::cout << count(q.begin(), q.end(), true) << std::endl;
        }
    }
    
    return 0;
}
