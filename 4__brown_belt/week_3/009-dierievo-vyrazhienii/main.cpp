#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class ValueExpression : public Expression {
   public:
    explicit ValueExpression(int value) : value(value) {}
    int Evaluate() const override { return value; }
    string ToString() const override { return to_string(value); }

   private:
    int value;
};

class SumExpression : public Expression {
   public:
    SumExpression(ExpressionPtr left, ExpressionPtr right) : left(move(left)), right(move(right)) {}

    int Evaluate() const override { return left->Evaluate() + right->Evaluate(); }
    string ToString() const override {
        stringstream ss;
        ss                                       //
            << "(" << left->ToString() << ")"    //
            << "+"                               //
            << "(" << right->ToString() << ")";  //
        return ss.str();
    }

   private:
    ExpressionPtr left, right;
};
class ProductExpression : public Expression {
   public:
    ProductExpression(ExpressionPtr left, ExpressionPtr right) : left(move(left)), right(move(right)) {}

    int Evaluate() const override { return left->Evaluate() * right->Evaluate(); }
    string ToString() const override {
        stringstream ss;
        ss                                       //
            << "(" << left->ToString() << ")"    //
            << "*"                               //
            << "(" << right->ToString() << ")";  //
        return ss.str();
    }

   private:
    ExpressionPtr left, right;
};

ExpressionPtr Value(int value) {
    return make_unique<ValueExpression>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<SumExpression>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<ProductExpression>(move(left), move(right));
}

string Print(const Expression* e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}