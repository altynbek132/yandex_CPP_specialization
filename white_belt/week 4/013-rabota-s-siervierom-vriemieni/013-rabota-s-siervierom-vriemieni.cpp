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

#include <numeric>

using namespace std;

void txt() {
  const char *maslo = std::getenv("maslo");
  if (!maslo) {
    return;
  }
  
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// ==================================


string AskTimeServer() {
  /* Для тестирования повставляйте сюда код, реализующий различное поведение этой функии:
     * нормальный возврат строкового значения
     * выброс исключения system_error
     * выброс другого исключения с сообщением.
  */
}

class TimeServer {
 public:
  string GetCurrentTime() {
    try {
      last_fetched_time = AskTimeServer();
    } catch (system_error &ex) {
    }
    return last_fetched_time;
    /* Реализуйте этот метод:
        * если AskTimeServer() вернула значение, запишите его в last_fetched_time и верните
        * если AskTimeServer() бросила исключение system_error, верните текущее значение
        поля last_fetched_time
        * если AskTimeServer() бросила другое исключение, пробросьте его дальше.
    */
  }
 
 private:
  string last_fetched_time = "00:00:00";
};


// ==================================

int main() {
  txt();

//  ifstream input("input.txt");
//  ofstream out("output.txt");
//  if (!input || !out) {
//    exit(1);
//  }
//
  TimeServer ts;
  try {
    cout << ts.GetCurrentTime() << endl;
  } catch (exception &e) {
    cout << "Exception got: " << e.what() << endl;
  }
  
  
  return 0;
}
