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
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)


//int main() {
//  txt();
//
////  ifstream input("input.txt");
////  ofstream out("output.txt");
////  if (!input || !out) {
////    exit(1);
////  }
////
//
//  return 0;
//}

#include <iostream>
using namespace std;

class Rational {
 public:
  Rational() : numerator(0), denominator(1) {}
  
  Rational(int numerator, int denominator) {
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

int test1() {
  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      cout << "Rational(3, 10) != 3/10" << endl;
      return 1;
    }
  }
  
  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(8, 12) != 2/3" << endl;
      return 2;
    }
  }
  
  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(-4, 6) != -2/3" << endl;
      return 3;
    }
  }
  
  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(4, -6) != -2/3" << endl;
      return 3;
    }
  }
  
  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      cout << "Rational(0, 15) != 0/1" << endl;
      return 4;
    }
  }
  
  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
      cout << "Rational() != 0/1" << endl;
      return 5;
    }
  }
  return 0;
}

int test2() {
  
  {
    Rational r1(4, 6);
    Rational r2(2, 3);
    bool equal = r1 == r2;
    if (!equal) {
      cout << "4/6 != 2/3" << endl;
      return 1;
    }
  }
  
  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a + b;
    bool equal = c == Rational(2, 1);
    if (!equal) {
      cout << "2/3 + 4/3 != 2" << endl;
      return 2;
    }
  }
  
  {
    Rational a(5, 7);
    Rational b(2, 9);
    Rational c = a - b;
    bool equal = c == Rational(31, 63);
    if (!equal) {
      cout << "5/7 - 2/9 != 31/63" << endl;
      return 3;
    }
  }
  
  return 0;
}

int positive_denom() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }
  
  {
    Rational a(5, 4);
    Rational b(15, 8);
    Rational c = a / b;
    bool equal = c == Rational(2, 3);
    if (!equal) {
      cout << "5/4 / 15/8 != 2/3" << endl;
      return 2;
    }
  }
  
  return 0;
  
}

int test4() {
  {
    ostringstream output;
    output << Rational(-6, 8);
    string str = output.str();
    string sadf = "-3/4";
    if (str != sadf) {
      cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
      std::cout << str << std::endl;
      return 1;
    }
  }
  
  {
    istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      cout << "5/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }
  
  {
    istringstream input("");
    Rational r;
    bool correct = !(input >> r);
    if (!correct) {
      cout << "Read from empty stream works incorrectly" << endl;
      return 3;
    }
  }
  
  {
    istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
      return 4;
    }
    
    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
      return 5;
    }
  }
  
  {
    istringstream input1("1*2"), input2("1/"), input3("/4");
    Rational r1, r2, r3;
    input1 >> r1;
    input2 >> r2;
    input3 >> r3;
    bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
    if (!correct) {
      cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
           << r1 << " " << r2 << " " << r3 << endl;
      
      return 6;
    }
  }
  
  return 0;
  
}

int test5() {
  {
    const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    if (rs.size() != 3) {
      cout << "Wrong amount of items in the set" << endl;
      return 1;
    }
    
    vector<Rational> v;
    for (auto x : rs) {
      v.push_back(x);
    }
    if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
      cout << "Rationals comparison works incorrectly" << endl;
      return 2;
    }
  }
  
  {
    map<Rational, int> count;
    ++count[{1, 2}];
    ++count[{1, 2}];
    
    ++count[{2, 3}];
    
    if (count.size() != 2) {
      cout << "Wrong amount of items in the map" << endl;
      return 3;
    }
  }
  
  return 0;
  
}

int main() {
    if (test1()) {
        std::cout << "test1" << std::endl;
    };
    if (test2()) {
        std::cout << "test2" << std::endl;
    };
    if (positive_denom()) {
        std::cout << "positive_denom" << std::endl;
    };
    if (test4()) {
        std::cout << "test4" << std::endl;
    };
    if (test5()) {
        std::cout << "test5" << std::endl;
    };
    
    cout << "OK" << endl;
    return 0;
}
