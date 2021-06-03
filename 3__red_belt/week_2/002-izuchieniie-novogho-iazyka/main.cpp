#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Learner {
   private:
    set<string> dict;

   public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if (dict.find(word) == dict.end()) {
                ++newWords;
                dict.insert(word);
            }
        }
        return newWords;
    }

    vector<string> KnownWords() { return {dict.begin(), dict.end()}; }
};

int main() {
    Learner asdf;
    return 0;
}
