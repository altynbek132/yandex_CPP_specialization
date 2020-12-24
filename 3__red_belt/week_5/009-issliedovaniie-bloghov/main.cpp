#include <bits/stdc++.h>
#include <profile.h>
#include <test_runner.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#define dout(arg) \
    {}

#ifdef MASLO

#define dout(arg) \
    { std::cout << (arg) << std::endl; }

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
#include <vector>

using namespace std;

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
// ==========================================

#include "profile.h"
#include "test_runner.h"

#include <map>
#include <ostream>
#include <string>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other);
    friend ostream& operator<<(ostream& os, const Stats& stats);
};

void Stats::operator+=(const Stats& other) {
    for (const auto& [key, value] : other.word_frequences) {
        word_frequences[key] += value;
    }
}

ostream& operator<<(ostream& os, const Stats& stats) {
    os << "word_frequences: " << stats.word_frequences;
    return os;
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats stats;
    istringstream is(line);
    string word;
    while (is >> word) {
        if (key_words.count(word)) {
            stats.word_frequences[std::move(word)]++;
        }
    }
    return stats;
}

template <typename Collection>
Stats ExploreLines(const set<string>& key_words, const Collection& lines) {
    Stats stats;
    for (const auto& line : lines) {
        stats += ExploreLine(key_words, line);
        dout(stats);
    }
    return stats;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    std::vector<string> lines;
    std::string line;
    while (getline(input, line)) {
        lines.push_back(std::move(line));
        line.clear();
    }
    dout(lines);

    const auto lines_pages = Paginate(lines, 2000);
    std::vector<future<Stats>> futures;
    futures.reserve(lines_pages.size());
    for (const auto& lines_page : lines_pages) {
        futures.push_back(async([&] { return ExploreLines(key_words, lines_page); }));
    }

    Stats result;
    for (auto& f : futures) {
        result += f.get();
    }
    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
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

// ==========================================
