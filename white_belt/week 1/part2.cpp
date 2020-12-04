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
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

//struct Person {
//    string name;
//    string surname;
//    int age;
//};

int types1() {
  int x = -5;
  double p = 3.14;
  bool logical_value = false;
  char symbol = 'Z';
  
  std::string str = "Hello, World!";
  std::vector<int> nums = {1, 2, 3, 4};
  
  std::map<string, int> name_to_value;
  name_to_value["one"] = 1;
  name_to_value["two"] = 2;
  
  cout << "two is " << name_to_value["one"] << endl;
  
  vector<Person> staff;
  staff.push_back({"Ivan", "Ivanov", 54});
  staff.push_back({"Petr", "Petrov", 27});
  
  cout << staff[0].surname;
  
  return 0;
}

void ops2() {
  int x = 4;
  int y = 5;
//    can compare vectors and strings
  if (x == y) {
    cout << "equal";
  } else {
    cout << "not equal";
  }
}

void container_ops() {
  string s = "abcdef";
  for (auto c: s) {
    cout << c << ", ";
  }
  
}

void cincout() {
  int x = 4;
  string y = "hello";
  cout << x << " " << y;
  
}

int main() {
  container_ops();
  
  return 0;
}
