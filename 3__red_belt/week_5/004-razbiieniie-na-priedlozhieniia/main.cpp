#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> res;
    auto first = tokens.begin();
    while (first != tokens.end()) {
        auto it =
            find_if(first, tokens.end(), [](const Token& token) { return token.IsEndSentencePunctuation(); });
        it = find_if(it, tokens.end(), [](const Token& token) { return !token.IsEndSentencePunctuation(); });
        res.push_back({move_iterator(first), move_iterator(it)});
        first = it;
    }
    return res;
}

struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const { return is_end_sentence_punctuation; }

    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
                 vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
                 vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"},
                                                       {"into"},
                                                       {"sentences"},
                                                       {"!", true},
                                                       {"!", true},
                                                       {"Without"},
                                                       {"copies"},
                                                       {".", true}})),
                 vector<Sentence<TestToken>>({
                     {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                     {{"Without"}, {"copies"}, {".", true}},
                 }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
