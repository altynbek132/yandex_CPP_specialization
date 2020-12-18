//
// Created by Addmin on 03.12.2020.
//

// #include <bits/stdc++.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pi;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

class FunctionPart {
 public:
  FunctionPart(char op, double rhs) : op(op), rhs(rhs) {}
  double Apply(double lhs) const {
    if (op == '+') {
      return lhs + rhs;
    }
    if (op == '-') {
      return lhs - rhs;
    }
    if (op == '*') {
      return lhs * rhs;
    }
    if (op == '/') {
      return lhs / rhs;
    }
    return 0;
  }
  void Invert() {
    if (op == '+') {
      op = '-';
      return;
    }
    if (op == '-') {
      op = '+';
      return;
    }
    if (op == '*') {
      op = '/';
      return;
    }
    if (op == '/') {
      op = '*';
      return;
    }
  }
 private:
  char op;
  double rhs;
};

class Function {
 public:
  void AddPart(char op, double value) {
    operations.emplace_back(op, value);
  }
  void Invert() {
    for (auto &fPart : operations) {
      fPart.Invert();
    }
    reverse(operations.begin(), operations.end());
  }
  double Apply(double operand) const {
    for_each(operations.begin(),
             operations.end(),
             [&operand](const FunctionPart &fPart) { operand = fPart.Apply(operand); });
    return operand;
  }
 private:
  vector<FunctionPart> operations;
};

Function MakeWeightComputer(const Params &params,
                            const Image &image) {
  Function function;
  function.AddPart('*', params.a);
  function.AddPart('-', image.freshness * params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params &params, const Image &image) {
  Function function = MakeWeightComputer(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params &params,
                              const Image &image,
                              double weight) {
  Function function = MakeWeightComputer(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl; // 72
  cout << ComputeQualityByWeight(params, image, 52) << endl; // 5
  return 0;
}
