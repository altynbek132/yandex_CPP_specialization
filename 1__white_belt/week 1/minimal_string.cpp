// #include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <set>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>
#include <tuple>
#include <utility>

using namespace std;

int main() {
    string str;
    cin>>str;
    for (int i = 0; i < 2; ++i) {
        string str2;
        cin>>str2;
        str = min(str, str2);
    }
    cout<<str;


    return 0;
}
