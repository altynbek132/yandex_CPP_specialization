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
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================

#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table
template<class T>
class Table {
 public:
  Table(size_t rows, size_t cols) : matrix(
      vector(rows, vector<T>(cols))
  ) {}
  
  vector<T> &operator[](size_t row) {
      return matrix.at(row);
  }
  
  const vector<T> &operator[](size_t row) const {
      return matrix.at(row);
  }
  
  void Resize(size_t rows, size_t cols) {
      matrix.resize(rows);
      for (auto &row : matrix) {
          row.resize(cols);
      }
  }
  
  pair<size_t, size_t> Size() const {
      if (!matrix.empty() && !matrix[0].empty()) {
          return {matrix.size(), matrix[0].size()};
      }
      
      return {0, 0};
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


// ==========================================
