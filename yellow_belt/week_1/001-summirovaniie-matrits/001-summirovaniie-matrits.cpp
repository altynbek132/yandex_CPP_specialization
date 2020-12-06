// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

#include <numeric>

using namespace std;

void txt() {
    const char *maslo = std::getenv("maslo");
    if (!maslo) {
        return;
    }
    
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

void ensure(istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(ios::failbit);
        throw exception();
    }
    input.ignore(1);
}
void ensure(istream &input) {
    if (!input) {
        throw exception();
    }
}
void ensure(bool state) {
    if (!state) {
        throw exception();
    }
}

stringstream stream_line(istream &input) {
    string line;
    while (line.empty() && !input.eof()) {
        getline(input, line);
    }
    stringstream input_stream(line);
    return input_stream;
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// ==================================

class Matrix {
 public:
  Matrix() = default;
  Matrix(int rows, int cols) {
      Reset(rows, cols);
  }
  void Reset(int new_rows, int new_cols) {
      validate(new_rows, new_cols);
      if (new_rows == 0 || new_cols == 0) {
          new_rows = new_cols = 0;
      }
      data.assign(new_rows, vector<int>(new_cols));
  }
  [[nodiscard]] int At(int row, int col) const {
      return data.at(row).at(col);
  }
  int &At(int row, int col) {
      return data.at(row).at(col);
  }
  [[nodiscard]] int GetNumRows() const {
      return data.size();
  }
  [[nodiscard]] int GetNumColumns() const {
      if (data.empty()) {
          return 0;
      }
      return data[0].size();
  }
  
  static void validate(int rows, int cols) {
      if (rows < 0 || cols < 0) {
          throw out_of_range("index cannot be negative");
      }
  }
 
 private:
  vector<vector<int>> data;
  
  void validate_at(int row, int col) const {
      validate(row, col);
      if (row > GetNumRows() || col > GetNumColumns()) {
          throw out_of_range("index cannot be negative");
      }
  }
};

istream &operator>>(istream &in, Matrix &m) {
    int rows, cols;
    stringstream input_stream = stream_line(in);
    ensure(input_stream >> rows);
    ensure(input_stream >> cols);
    
    m = Matrix(rows, cols);
    for (size_t row = 0; row < rows; ++row) {
        stringstream input_stream = stream_line(in);
        for (size_t col = 0; col < cols; ++col) {
            ensure(input_stream >> m.At(row, col));
        }
        ensure(input_stream.eof());
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix &m) {
    const int rows = m.GetNumRows();
    const int cols = m.GetNumColumns();
    out << rows << " " << cols << std::endl;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            out << m.At(i, j);
            if (j != cols - 1) {
                out << " ";
            }
        }
        out << std::endl;
    }
    return out;
}

bool operator==(const Matrix &m1, const Matrix &m2) {
    const int rows = m1.GetNumRows();
    const int cols = m1.GetNumColumns();
    const int rows2 = m2.GetNumRows();
    const int cols2 = m2.GetNumColumns();
    if (rows != rows2 || cols != cols2) {
        return false;
    }
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (m1.At(i, j) != m2.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    const int rows = m1.GetNumRows();
    const int cols = m1.GetNumColumns();
    const int rows2 = m2.GetNumRows();
    const int cols2 = m2.GetNumColumns();
    if (rows != rows2 || cols != cols2) {
        throw invalid_argument("matrix sizes are different");
    }
    Matrix m3(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            m3.At(i, j) = m1.At(i, j) + m2.At(i, j);
        }
    }
    return m3;
}

// ==================================

int run() {
    txt();

//  ifstream input("input.txt");
//  ofstream out("output.txt");
//  if (!input || !out) {
//    exit(1);
//  }
//
    Matrix one;
    Matrix two;
    
    cin >> one;
    cin >> two;
    auto three = one + two;
    cout << three << endl;
    
    return 0;
}

int main() {
    try {
        return run();
    } catch (exception &ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}
