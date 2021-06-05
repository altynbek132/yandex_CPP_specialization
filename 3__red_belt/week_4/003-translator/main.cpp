#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

class Translator {
   public:
    void Add(string_view source_view_, string_view target_view_) {
        string_view source_view = SaveString(source_view_);
        string_view target_view = SaveString(target_view_);

        forward[source_view] = target_view;
        backward[target_view] = source_view;
    }
    string_view TranslateForward(string_view source) const {
        auto it = forward.find(source);
        if (it == forward.end()) {
            return "";
        }
        return it->second;
    }
    string_view TranslateBackward(string_view target) const {
        auto it = backward.find(target);
        if (it == backward.end()) {
            return "";
        }
        return it->second;
    }

   private:
    map<string_view, string_view> forward, backward;
    set<string> data;

    string_view SaveString(string_view sv) {
        string str = string(sv.data());
        auto source_it = data.find(str);
        if (source_it == data.end()) {
            auto p = data.insert(str);
            source_it = p.first;
        }
        return *source_it;
    }
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}