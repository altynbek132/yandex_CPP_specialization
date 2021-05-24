#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

// Реализуйте здесь шаблонный класс Table

template <class T>
class Table {
   public:
    Table(size_t rows, size_t cols) : matrix(vector(rows, vector<T>(cols))) {}
    vector<T>& operator[](size_t row) { return matrix[row]; }
    const vector<T>& operator[](size_t row) const { return matrix[row]; }
    void Resize(size_t rows, size_t cols) {
        matrix.resize(rows);
        for (auto& row : matrix) {
            row.resize(cols);
        }
    }

    pair<size_t, size_t> Size() const {
        if (matrix.empty() || matrix[0].empty()) {
            return {0, 0};
        }
        return {matrix.size(), matrix[0].size()};
    }

   private:
    vector<vector<T>> matrix;
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
