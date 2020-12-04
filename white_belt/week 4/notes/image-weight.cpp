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
#define F first
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


#include <algorithm>
#include <vector>
using namespace std;

class FunctionPart {
 public:
  FunctionPart(char new_operation, double new_value) {
    operation = new_operation;
    value = new_value;
  }
  double Apply(double source_value) const {
    if (operation == '+') {
      return source_value + value;
    } else {  // operation == '-'
      return source_value - value;
    }
  }
  void Invert() {
    if (operation == '+') {
      operation = '-';
    } else {  // operation == '-'
      operation = '+';
    }
  }
 private:
  char operation;
  double value;
};

class Function {
 public:
  void AddPart(char operation, double value) {
    parts.push_back({operation, value});
  }
  double Apply(double value) const {
    for (const FunctionPart &part : parts) {
      value = part.Apply(value);
    }
    return value;
  }
  void Invert() {
    for (FunctionPart &part : parts) {
      part.Invert();
    }
    reverse(begin(parts), end(parts));
  }
 private:
  vector<FunctionPart> parts;
};

Function MakeWeightComputer(const Params &params, const Image &image) {
  Function f;
  f.AddPart('-', image.freshness * params.a + params.b);
  f.AddPart('+', image.rating * params.c);
  return f;
}

double ComputeImageWeight(const Params &params, const Image &image) {
  double weight = image.quality;
  Function weightComputer = MakeWeightComputer(params, image);
  return weightComputer.Apply(image.quality);
}

double ComputeQualityByWeight(const Params &params, const Image &image, double weight) {
  Function weightComputer = MakeWeightComputer(params, image);
  weightComputer.Invert();
  return weightComputer.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  std::cout << ComputeImageWeight(params, image) << std::endl; // 36
  std::cout << ComputeQualityByWeight(params, image, 46) << std::endl; // 20
  
  return 0;
}







