// ==========================================
// sample for main:

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <bits/stdc++.h>
//
//#include <cstdlib>
//#include <iostream>
//
//#include <set>
//#include <map>
//#include <deque>
//#include <sstream>
//#include <string>
//#include <iterator>
//#include <tuple>
//#include <algorithm>
//#include <utility>
//#include <vector>

//#include <numeric>
//
//#include <iomanip>
//#include <fstream>
//
//#include <type_traits>
//
//#include <limits>
//
//#include <cassert>
//#include <random>


using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif

#ifdef MASLO

enum class Gender {
  FEMALE,
  MALE
};


struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person &lhs, const Person &rhs) {
          return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

#endif

void PrintStats(vector<Person> persons) {
    std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;
    auto females_end = partition(persons.begin(), persons.end(), [](const Person &p) {
      return p.gender == Gender::FEMALE;
    });
    /*
    Median age = 40
    Median age for females = 40
    Median age for males = 55
    Median age for employed females = 40
    Median age for unemployed females = 80
    Median age for employed males = 55
    Median age for unemployed males = 78
    */
    std::cout << "Median age for females = " << ComputeMedianAge(persons.begin(), females_end) << std::endl;
    std::cout << "Median age for males = " << ComputeMedianAge(females_end, persons.end()) << std::endl;
    
    auto females_employed_end = partition(persons.begin(), females_end, [](const Person &p) {
      return p.is_employed;
    });
    
    std::cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), females_employed_end)
              << std::endl;
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(females_employed_end, females_end)
              << std::endl;
    auto male_employed_end = partition(females_end, persons.end(), [](const Person &p) {
      return p.is_employed;
    });
    std::cout << "Median age for employed males = " << ComputeMedianAge(females_end, male_employed_end) << std::endl;
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(male_employed_end, persons.end())
              << std::endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}


// ==========================================
