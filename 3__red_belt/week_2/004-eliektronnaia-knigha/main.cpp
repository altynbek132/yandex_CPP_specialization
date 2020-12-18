#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Q - count of queries

class ReadingManager {
 public:
  ReadingManager() :
      user_to_pages(TOTAL_USERS + 1, -1),
      page_count_to_users(TOTAL_PAGES + 1, 0),
      user_count(0) {}
  
  void Read(int user_id_, int page_count_);
  
  [[nodiscard]] double Cheer(int user_id_) const;
 
 private:
  vector<int> user_to_pages;
  vector<size_t> page_count_to_users;
  size_t user_count;
  
  static const size_t TOTAL_PAGES = 1000;
  static const size_t TOTAL_USERS = 1e5;
};

void ReadingManager::Read(int user_id_, int page_count_) {
    auto &page_count = user_to_pages[user_id_];
    if (page_count == -1) {
        user_count++;
    } else {
        page_count_to_users[page_count]--;
    }
    page_count = page_count_;
    page_count_to_users[page_count]++;
}

double ReadingManager::Cheer(int user_id_) const {
    auto page_count = user_to_pages[user_id_];
    if (page_count == -1) {
        return 0;
    }
    
    size_t less = accumulate(page_count_to_users.begin(), next(page_count_to_users.begin(), page_count), 0u);
    if (user_count == 1) { return 1; }
    return (double) less / (user_count - 1);
}




int main() {
#ifndef MASLO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    
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

// ==========================================
