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
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

struct Student {
  Student(const string &first, const string &last, int day, int month, int year)
      : first(first), last(last), day(day), month(month), year(year) {}
  string first, last;
  int day, month, year;
};

int main() {
  txt();

//  ifstream input("input.txt");
//  ofstream out("output.txt");
//  if (!input || !out) {
//    exit(1);
//  }
//
  vector<Student> students;
  int N;
  cin >> N;
  for (size_t i = 0; i < N; ++i) {
    string first, last;
    int day, month, year;
    cin >> first >> last >> day >> month >> year;
    students.emplace_back(first, last, day, month, year);
  }
  
  int M;
  cin >> M;
  for (size_t i = 0; i < M; ++i) {
    string operation_code;
    int num;
    cin >> operation_code >> num;
    --num;
    if (num < 0 || num >= students.size()) {
      cout << "bad request" << std::endl;
      continue;
    }
    
    const auto &student = students[num];
    if (operation_code == "name") {
      cout << student.first << " " << student.last << std::endl;
    } else if (operation_code == "date") {
      cout << student.day << "." << student.month << "." << student.year << std::endl;
    } else {
      cout << "bad request" << std::endl;
    }
  }
  
  return 0;
}

