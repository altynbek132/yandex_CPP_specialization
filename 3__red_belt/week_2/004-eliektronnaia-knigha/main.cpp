#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/*
HAS CHEAP READ AND COSTLY CHEER(P)
Q : queries
n : peoples
P : pages
Tmax : max time

implementation:

 vector<people_count> counts(P)
 vector person_to_pageCount

constructor
 P
read
 correct position of person in counts
 1
cheer
 count prev, total
 P (always)

overall
Q = 10**6
n = 10**5
P = 10**3

op_per_s = 10**9
# 10-50
coeff = 50
Tmax = 4

time = Q * (P)
print(time)
print(time<4)

 // ===============================================================
IMPLEMENTED:
 HAS CHEAP CHEER AND COSTLY READ(P)
Q : queries
n : peoples
P : pages
Tmax : max time

implementation:

counting sum of pages
vector as map person_to_page

constructor
read
total : n people by P pages: nP,
 P
cheer
 1

overall
Q = 10**6
n = 10**5
P = 10**3

op_per_s = 10**9
# 10-50
coeff = 50
Tmax = 4

time = coeff * Q * (n*P/Q) / op_per_s
print(time)
print(time<4)

 * */
class ReadingManager {
   public:
    ReadingManager()
        : page_to_persons_prefix_sum(MAX_PAGE_COUNT + 1),
          person_to_pages(MAX_USER_COUNT + 1, -1),
          user_count(0) {}

    void Read(int user_id, int page_count) {
        auto& pages_ref = person_to_pages[user_id];
        bool hasRead = pages_ref != -1;
        if (hasRead) {
            auto old = pages_ref;
            auto cur = page_count;
            for (int i = old + 1; i < cur + 1; ++i) {
                page_to_persons_prefix_sum[i]--;
            }
            pages_ref = cur;
        } else {
            user_count++;
            auto cur = page_count;
            for (int i = cur + 1; i < MAX_PAGE_COUNT; ++i) {
                page_to_persons_prefix_sum[i]++;
            }
            pages_ref = cur;
        }
    }

    double Cheer(int user_id) const {
        if (bool hasRead = person_to_pages[user_id] != -1; !hasRead) {
            return 0;
        }
        if (user_count == 1) {
            return 1;
        }
        auto page_count = person_to_pages[user_id];
        auto persons_before = page_to_persons_prefix_sum[page_count];
        return 1.0 * persons_before / (user_count - 1);
    }

    void debug() {
        vector<User_stat> user_stats;
        for (size_t user_id = 0; user_id < MAX_USER_COUNT; ++user_id) {
            auto page_count = person_to_pages[user_id];
            if (page_count != -1) {
                user_stats.emplace_back(user_id, page_count, Cheer(user_id));
            }
        }
        sort(user_stats.begin(), user_stats.end(),
             [](const User_stat& lhs, const User_stat& rhs) { return lhs.page_count < rhs.page_count; });

        std::cout << "printing all users sorted by read pages count:" << std::endl;
        User_stat::printHeader();
        std::cout << std::endl;

        for (auto& user_stat : user_stats) {
            user_stat.printRow();
            std::cout << std::endl;
        }
    }

    struct User_stat {
        friend ostream& operator<<(ostream& os, const User_stat& stat) {
            os << "user_id: " << left << setw(5) << stat.user_id << " page_count: " << left << setw(5)
               << stat.page_count << " cheer: " << left << setw(5) << stat.cheer;
            return os;
        }
        void printRow() {
            cout << left << setw(15) << user_id     //
                 << left << setw(20) << page_count  //
                 << left << setw(12) << cheer;      //
        }
        static void printHeader() {
            cout << left << setw(15) << "user_id: "     //
                 << left << setw(20) << "page_count: "  //
                 << left << setw(12) << "cheer: ";      //
        }
        User_stat(int userId, int pageCount, double cheer)
            : user_id(userId), page_count(pageCount), cheer(cheer) {}
        int user_id, page_count;
        double cheer;
    };

   private:
    // excluding
    static const int MAX_PAGE_COUNT = 1000 + 1;
    static const int MAX_USER_COUNT = 1e5 + 1;

    vector<size_t> page_to_persons_prefix_sum;
    // -1: never read
    vector<int> person_to_pages;
    size_t user_count;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
