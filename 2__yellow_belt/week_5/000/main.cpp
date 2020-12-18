#include <bits/stdc++.h>

#include <utility>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
      txt();
//      TestAll();
  }
};

Prerun maslo;
#endif

struct Node {
  virtual int Evaluate() const = 0;
};

struct Variable : public Node {
  explicit Variable(const int &x) : x(x) {}
  
  int Evaluate() const override {
      return x;
  }
 
 private:
  const int &x;
};

struct Value : public Node {
  explicit Value(uint8_t val) : val(val) {}
  
  int Evaluate() const override {
      return val;
  }
 
 private:
  const uint8_t val;
};

struct Op : public Node {
  explicit Op(char op) :
      
      precedence([op] {
        if (op == '*' || op == '/') {
            return 2;
        }
        return 1;
      }()), op(op) {}
  
  void set_left(shared_ptr<Node> left_) { left = std::move(left_); }
  
  void set_right(shared_ptr<Node> right_) { right = std::move(right_); }
  
  int Evaluate() const override {
      switch (op) {
          case '+' : {
              return left->Evaluate() + right->Evaluate();
              break;
          }
          case '-' : {
              return left->Evaluate() - right->Evaluate();
              break;
          }
          case '*' : {
              return left->Evaluate() * right->Evaluate();
              break;
          }
          case '/' : {
              return left->Evaluate() / right->Evaluate();
              break;
          }
          default: {
              return 0;
              break;
          }
      }
  }
  
  const uint8_t precedence;
 
 private:
  const char op;
  shared_ptr<Node> left, right;
};

template<class It>
shared_ptr<Node> Parse(It begin, It end, const int &x) {
    if (begin == end) {
        return make_shared<Value>(0);
    }
    
    stack<shared_ptr<Node>> values;
    stack<shared_ptr<Op>> ops;
    
    auto pop_ups = [&](uint8_t precedence) {
      while (!ops.empty() && ops.top()->precedence >= precedence) {
          auto op = ops.top();
          ops.pop();
          auto right = values.top();
          values.pop();
          auto left = values.top();
          values.pop();
          
          op->set_left(left);
          op->set_right(right);
          values.push(op);
      }
    };
    
    while (begin != end) {
        const auto &ch = *begin;
        if (ch == 'x') {
            values.push(make_shared<Variable>(x));
        } else if (ch >= '0' && ch <= '9') {
            values.push(make_shared<Value>(ch - '0'));
        } else if (ch == '+' || ch == '-') {
            pop_ups(1);
            ops.push(make_shared<Op>(ch));
        } else if (ch == '*' || ch == '/') {
            pop_ups(2);
            ops.push(make_shared<Op>(ch));
        }
        begin++;
    }
    
    while (!ops.empty()) {
        pop_ups(0);
    }
    return values.top();
}

int main() {
    string tokens;
    getline(cin, tokens);
    int x;
    auto expr = Parse(tokens.begin(), tokens.end(), x);
    while (cin >> x) {
        std::cout << expr->Evaluate() << std::endl;
    }
    
    return 0;
}


// ==========================================
