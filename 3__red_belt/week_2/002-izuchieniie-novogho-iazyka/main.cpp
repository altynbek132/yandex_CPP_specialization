#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
//      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Learner {
 private:
  set<string> dict;
 
 public:
  int Learn(const vector<string> &words) {
      int newWords = 0;
      for (const auto &word : words) {
          if (dict.count(word) == 0) {
              ++newWords;
              dict.insert(word);
          }
      }
      return newWords;
  }
  
  vector<string> KnownWords() {
      return {dict.begin(), dict.end()};
  }
};

int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}

// ==========================================
