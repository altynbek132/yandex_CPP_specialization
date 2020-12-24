#include <bits/stdc++.h>
#include <profile.h>
#include <test_runner.h>

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

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token>
using Sentence = vector<Token>;

//template<typename It>
//struct MyMoveIt : public It {
//  It it;
//
//  typename It::value_type operator*() {
//      return move(*it);
//  }
//};
//
//template<typename It>
//MyMoveIt<It> moveIt(It it) {
//    return {it};
//}

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token
    vector<Sentence<Token>> res;
    auto first = tokens.begin();
    while (first != tokens.end()) {
        auto it =
            find_if(first, tokens.end(), [](const Token &token) { return token.IsEndSentencePunctuation(); });
        it =
            find_if(it, tokens.end(), [](const Token &token) { return !token.IsEndSentencePunctuation(); });
        res.push_back({move_iterator(first), move_iterator(it)});
        first = it;
    }
    return res;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;
  
  bool IsEndSentencePunctuation() const {
      return is_end_sentence_punctuation;
  }
  
  bool operator==(const TestToken &other) const {
      return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream &operator<<(ostream &stream, const TestToken &token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
        vector<Sentence<TestToken>>({
                                        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                    })
    );
    
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
        vector<Sentence<TestToken>>({
                                        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                    })
    );
    
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"},
                                              {"copies"}, {".", true}})),
        vector<Sentence<TestToken>>({
                                        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                        {{"Without"}, {"copies"}, {".", true}},
                                    })
    );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}


// ==========================================
