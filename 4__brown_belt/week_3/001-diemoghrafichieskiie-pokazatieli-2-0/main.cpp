#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
   public:
    IteratorRange(Iterator begin, Iterator end) : first(begin), last(end) {}

    Iterator begin() const { return first; }

    Iterator end() const { return last; }

   private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream& input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person& p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }

    return result;
}

struct StatsData {
    optional<string> most_popular_male_name;
    optional<string> most_popular_female_name;
    vector<int> cumulative_wealth;
    vector<Person> sorted_by_age;
};

template <typename Iter>
optional<string> FindMostPopularName(IteratorRange<Iter> range) {
    auto begin = range.begin();
    auto end = range.end();

    if (begin == end) {
        return nullopt;
    }

    sort(begin, end, [](const Person& lhs, const Person& rhs) { return lhs.name < rhs.name; });
    string* most_popular_name = &begin->name;
    size_t count = 1;
    for (auto it = begin; it != end;) {
        auto same_name_end =
            find_if_not(it, end, [it](const Person& person) { return it->name == person.name; });
        size_t cur_count = distance(it, same_name_end);
        if (cur_count > count || (cur_count == count && it->name < *most_popular_name)) {
            most_popular_name = &it->name;
            count = cur_count;
        }

        it = same_name_end;
    }
    return *most_popular_name;
}

StatsData BuildStatsData(vector<Person> people) {
    StatsData res;

    {
        auto middle =
            partition(people.begin(), people.end(), [](const Person& person) { return person.is_male; });
        auto males = IteratorRange(people.begin(), middle);
        auto females = IteratorRange(middle, people.end());
        res.most_popular_female_name = FindMostPopularName(females);
        res.most_popular_male_name = FindMostPopularName(males);
    }

    {
        sort(people.begin(), people.end(),
             [](const Person& lhs, const Person& rhs) { return lhs.income > rhs.income; });
        auto& cumulative_wealth = res.cumulative_wealth;
        cumulative_wealth.resize(people.size());
        if (!people.empty()) {
            cumulative_wealth[0] = people[0].income;
            for (size_t i = 1; i < people.size(); ++i) {
                cumulative_wealth[i] = people[i].income + cumulative_wealth[i - 1];
            }
        }
    }

    sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; });
    res.sorted_by_age = std::move(people);

    return res;
}

int main() {
    const StatsData stats = BuildStatsData(ReadPeople(cin));

    for (string command; cin >> command;) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;

            auto adult_begin = lower_bound(begin(stats.sorted_by_age), end(stats.sorted_by_age), adult_age,
                                           [](const Person& lhs, int age) { return lhs.age < age; });

            cout << "There are " << std::distance(adult_begin, end(stats.sorted_by_age))
                 << " adult people for maturity age " << adult_age << '\n';
        } else if (command == "WEALTHY") {
            int count;
            cin >> count;
            cout << "Top-" << count << " people have total income " << stats.cumulative_wealth[count - 1]
                 << '\n';
        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;
            const auto& most_popular_name =
                gender == 'M' ? stats.most_popular_male_name : stats.most_popular_female_name;
            if (most_popular_name) {
                cout << "Most popular name among people of gender " << gender << " is " << *most_popular_name
                     << '\n';
            } else {
                cout << "No people of gender " << gender << '\n';
            }
        }
    }
}
