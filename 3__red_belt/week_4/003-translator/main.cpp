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

#include "test_runner.h"
#include <string>
#include <vector>

using namespace std;

class Translator {
 public:
  void Add(string_view source, string_view target);
  string_view TranslateForward(string_view source) const;
  string_view TranslateBackward(string_view target) const;
 
 private:
  list<string> words;
  map<string_view, string_view> source_to_target;
  map<string_view, string_view> target_to_source;
  
  string_view GetStringView(string_view);
  static string_view Translate(const map<string_view, string_view> &, string_view);
};

void Translator::Add(string_view source, string_view target) {
    const string_view source_v = GetStringView(source);
    const string_view target_v = GetStringView(target);
    source_to_target[source_v] = target_v;
    target_to_source[target_v] = source_v;
}

string_view Translator::TranslateForward(string_view source) const {
    return Translate(source_to_target, source);
}

string_view Translator::TranslateBackward(string_view target) const {
    return Translate(target_to_source, target);
}

string_view Translator::GetStringView(const string_view str_v) {
    for (const auto *dict_p : {&source_to_target, &target_to_source}) {
        auto it = dict_p->find(str_v);
        if (it != dict_p->end()) {
            return it->first;
        }
    }
    return words.emplace_back(str_v);
}

string_view Translator::Translate(const map<string_view, string_view> &dict, const string_view str_v) {
    auto it = dict.find(str_v);
    if (it == dict.end()) { return {}; }
    return it->second;
}

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

// ==========================================
