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

class Rational {
 public:
  Rational() : numerator(0), denominator(1) {}
  
  Rational(int numerator, int denominator) {
    if (denominator == 0) {
      throw invalid_argument("denominator could not be zero");
    }
    
    int gcd_number = gcd(numerator, denominator);
    this->numerator = (numerator * denominator / abs(denominator)) / gcd_number;
    this->denominator = abs(denominator) / gcd_number;
    if (numerator == 0) {
      this->denominator = 1;
    }
  }
  
  int Numerator() const {
    return numerator;
  }
  
  int Denominator() const {
    return denominator;
  }
 
 private:
  int numerator, denominator;
};

bool operator==(const Rational &lhs, const Rational &rhs) {
  return tuple(lhs.Numerator(), lhs.Denominator()) == tuple(rhs.Numerator(), rhs.Denominator());
}
Rational operator+(const Rational &lhs, const Rational &rhs) {
  return Rational(
      lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  );
}
Rational operator-(const Rational &lhs, const Rational &rhs) {
  return Rational(
      lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  );
}
Rational operator*(const Rational &lhs, const Rational &rhs) {
  return Rational(
      lhs.Numerator() * rhs.Numerator(),
      lhs.Denominator() * rhs.Denominator()
  );
}
Rational operator/(const Rational &lhs, const Rational &rhs) {
  if (rhs.Numerator() == 0) {
    throw domain_error("could not divide by zero");
  }
  return Rational(
      lhs.Numerator() * rhs.Denominator(),
      lhs.Denominator() * rhs.Numerator()
  );
}

istream &operator>>(istream &input, Rational &r) {
  int n, d;
  
  if (!(input >> n)) {
    input.setstate(ios_base::failbit);
    return input;
  }
  if (input.peek() != '/') {
    input.setstate(ios_base::failbit);
    return input;
  }
  if (!(input.ignore(1))) {
    input.setstate(ios_base::failbit);
    return input;
  }
  if (!(input >> d)) {
    input.setstate(ios_base::failbit);
    return input;
  }
  
  r = Rational(n, d);
  return input;
}

ostream &operator<<(ostream &out, const Rational &r) {
  out << r.Numerator() << "/" << r.Denominator();
  return out;
}

bool operator<(const Rational &lhs, const Rational &rhs) {
  return (
      lhs.Numerator() * rhs.Denominator() <
          rhs.Numerator() * lhs.Denominator()
  );
}

// ==================================

int main() {
//  txt();

//  ifstream input("input.txt");
//  ofstream out("output.txt");
//  if (!input || !out) {
//    exit(1);
//  }
//
  try {
    Rational r(1, 0);
    cout << "Doesn't throw in case of zero denominator" << endl;
    return 1;
  } catch (invalid_argument &ex) {
    std::cout << ex.what() << std::endl;
  }
  
  try {
    auto x = Rational(1, 2) / Rational(0, 1);
    cout << "Doesn't throw in case of division by zero" << endl;
    return 2;
  } catch (domain_error &ex) {
    std::cout << ex.what() << std::endl;
  }
  
  
  return 0;
}
