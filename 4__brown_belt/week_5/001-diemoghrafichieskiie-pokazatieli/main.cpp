#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

#ifdef MASLO
enum class Gender {
    FEMALE,
    MALE,
};

struct Person {
    int age;           // возраст
    Gender gender;     // пол
    bool is_employed;  // имеет ли работу
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(begin(range_copy), middle, end(range_copy),
                [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; });
    return middle->age;
}
#endif  // MASLO

/*
Median age =
Median age for females =
Median age for males =
Median age for employed females =
Median age for unemployed females =
Median age for employed males =
Median age for unemployed males =

 * */
void PrintStats(vector<Person> persons) {
    auto begin = persons.begin();
    auto end = persons.end();
    std::cout << "Median age = " << ComputeMedianAge(begin, end) << std::endl;
    //

    auto females_begin = begin;
    auto females_end =
        partition(begin, end, [](const Person& person) { return person.gender == Gender::FEMALE; });
    std::cout << "Median age for females = " << ComputeMedianAge(females_begin, females_end) << std::endl;

    auto males_begin = females_end;
    auto males_end = end;
    std::cout << "Median age for males = " << ComputeMedianAge(males_begin, males_end) << std::endl;
    //

    auto employedFemales_begin = females_begin;
    auto employedFemales_end =
        partition(females_begin, females_end, [](const Person& person) { return person.is_employed; });
    std::cout << "Median age for employed females = "
              << ComputeMedianAge(employedFemales_begin, employedFemales_end) << std::endl;

    auto unemployedFemales_begin = employedFemales_end;
    auto unemployedFemales_end = females_end;
    std::cout << "Median age for unemployed females = "
              << ComputeMedianAge(unemployedFemales_begin, unemployedFemales_end) << std::endl;
    //

    auto employedMales_begin = males_begin;
    auto employedMales_end =
        partition(males_begin, males_end, [](const Person& person) { return person.is_employed; });
    std::cout << "Median age for employed males = "
              << ComputeMedianAge(employedMales_begin, employedMales_end) << std::endl;

    auto unemployedMales_begin = employedMales_end;
    auto unemployedMales_end = males_end;
    std::cout << "Median age for unemployed males = "
              << ComputeMedianAge(unemployedMales_begin, unemployedMales_end) << std::endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},   {40, Gender::FEMALE, true},  {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},  {80, Gender::FEMALE, false}, {78, Gender::MALE, false},
        {10, Gender::FEMALE, false}, {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
