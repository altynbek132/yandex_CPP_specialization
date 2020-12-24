#include <bits/stdc++.h>
//#include <execution>
#include <algorithm>
#include <future>
#include <mutex>
#include "profile.h"
#include "test_runner.h"

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
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
   public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin), last(end), size_(distance(first, last)) {}

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

#include <vector>
#include "test_runner.h"
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    futures.reserve(matrix.size());

    // pages should be out of the loop in order to avoid invalidation of
    // references of it
    const auto pages = Paginate(matrix, 2000);
    for (const auto& rows : pages) {
        futures.push_back(async([&rows] {
            int64_t partial_sum = 0;
            for (const auto& row : rows) {
                partial_sum += accumulate(row.begin(), row.end(), 0);
            }
            return partial_sum;
        }));
    }

    int64_t sum = 0;
    for (auto& f : futures) {
        sum += f.get();
    }
    return sum;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}

// ==========================================
