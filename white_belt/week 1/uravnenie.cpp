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

#include <cmath>

using namespace std;

int main() {
    double A, B, C;
    cin >> A >> B >> C;

    if (A == 0) {
        cout << -C / B;
    } else {
        double delta = B * B - 4 * A * C;
        if (delta < 0) {

        } else if (delta == 0) {
            cout << (-B + sqrt(delta)) / (2 * A) << " ";
        } else {
            cout << (-B + sqrt(delta)) / (2 * A) << " ";
            cout << (-B - sqrt(delta)) / (2 * A);
        }
    }
    return 0;
}
