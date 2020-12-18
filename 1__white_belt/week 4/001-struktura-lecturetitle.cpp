//
// Created by Addmin on 03.12.2020.
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

struct Specialization {
  string value;
  explicit Specialization(const string &new_value) {
    value = new_value;
  }
};
struct Course {
  string value;
  explicit Course(const string &new_value) {
    value = new_value;
  }
};
struct Week {
  string value;
  explicit Week(const string &new_value) {
    value = new_value;
  }
};

struct LectureTitle {
  string specialization;
  string course;
  string week;
  LectureTitle(
      const Specialization &new_specialization,
      const Course &new_course,
      const Week &new_week
  ) {
    specialization = new_specialization.value;
    course = new_course.value;
    week = new_week.value;
  }
};

int main() {
  LectureTitle title(
      Specialization("C++"),
      Course("White belt"),
      Week("4th")
  );
//  =========
  LectureTitle title("C++", "White belt", "4th");
  
  LectureTitle title(string("C++"), string("White belt"), string("4th"));
  
  LectureTitle title = {"C++", "White belt", "4th"};
  
  LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};
  
  LectureTitle title(
      Course("White belt"),
      Specialization("C++"),
      Week("4th")
  );
  
  LectureTitle title(
      Specialization("C++"),
      Week("4th"),
      Course("White belt")
  );
  
  
  return 0;
}
