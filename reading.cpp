#include <vector>



class asdf {
};



enum class adddd {
};



class adddd3 {
};



enum class Lang {
  DE, FR, IT
};

struct Region {
};



class Foo {
  friend class AnotherClass;
 
 
 
 private:
  Foo *field1;
 public:
  int field2;
  
  Foo() {
      field1 = new Foo();
  }
  
  class InnerClass {
   public:
    static int x;
    static int y;
    int f();
    int g();
  };
};



int Foo::InnerClass::x = 25;

int Foo::InnerClass::f() { return 0; };
typedef Foo::InnerClass owner;       // define a typedef
int owner::y = 11;                   // use typedef with ::
int owner::g() { return 0; };



class AnotherClass {
};



struct TestInterface {
  static const int MAX = 42;
  static const int MIN = 0;
  virtual void method1() = 0;
  virtual void method2() = 0;
};
