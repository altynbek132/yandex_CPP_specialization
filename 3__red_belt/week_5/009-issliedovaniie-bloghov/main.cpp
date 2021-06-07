#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

template <typename Iterator>
class IteratorRange {
   public:
    IteratorRange(Iterator begin, Iterator end) : first(begin), last(end), size_(distance(first, last)) {}

    Iterator begin() const { return first; }

    Iterator end() const { return last; }

    size_t size() const { return size_; }

   private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator {
   private:
    vector<IteratorRange<Iterator>> pages;

   public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (size_t left = distance(begin, end); left > 0;) {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const { return pages.begin(); }

    auto end() const { return pages.end(); }

    size_t size() const { return pages.size(); }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}
#include "profile.h"
#include "test_runner.h"

#include <map>
#include <string>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other) {
        for (auto& [key, count] : other.word_frequences) {
            word_frequences[key] += count;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    stringstream ss(line);
    string word;
    Stats res;
    while (ss >> word) {
        if (key_words.count(word)) {
            res.word_frequences[move(word)]++;
        }
    }
    return res;
}

Stats ExplorePage(const set<string>& key_words, vector<string> lines) {
    Stats res;
    for (auto& line : lines) {
        res += ExploreLine(key_words, line);
    }
    return res;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    const int page_size = 5000;
    vector<string> lines;
    lines.reserve(page_size);
    vector<future<Stats>> futures;

    string line;
    while (getline(input, line)) {
        lines.push_back(move(line));
        if (lines.size() >= page_size) {
            futures.push_back(async(ExplorePage, ref(key_words), move(lines)));
            lines.reserve(page_size);
        }
    }
    if (!lines.empty()) {
        futures.push_back(async(ExplorePage, ref(key_words), move(lines)));
    }

    Stats res;
    for (auto& f : futures) {
        res += f.get();
    }
    return res;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    // true:
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {{"yangle", 6}, {"rocks", 2}, {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
