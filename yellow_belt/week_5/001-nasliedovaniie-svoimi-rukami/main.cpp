#include <bits/stdc++.h>

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
      TestAll();
  }
};

Prerun maslo;
#endif

// ==========================================

#include <iostream>

using namespace std;

class Animal {
 public:
  Animal(const string &name) : Name(name) {}
  
  const string Name;
};

class Dog : public Animal {
 public:
  Dog(const string &name) : Animal(name) {}
  
  void Bark() {
      cout << Name << " barks: woof!" << endl;
  }
};


int main() {
    
    return 0;
}


// ==========================================
