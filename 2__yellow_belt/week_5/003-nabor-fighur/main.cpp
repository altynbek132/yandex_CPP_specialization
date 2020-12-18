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
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================
const double PI = 3.14;

class Figure {
 public:
  Figure(string name) : name(std::move(name)) {}
  
  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;
 protected:
  const string name;
};

class Triangle : public Figure {
 public:
  Triangle(int a, int b, int c) : Figure("TRIANGLE"), a(a), b(b), c(c) {}
  
  string Name() const override {
      return name;
  }
  
  double Perimeter() const override {
      return a + b + c;
  }
  
  double Area() const override {
      double S = ((double) a + b + c) / 2;
      return sqrt(S * (S - a) * (S - b) * (S - c));
  }
 
 private:
  uint16_t a, b, c;
};

class Rect : public Figure {
 public:
  Rect(int width, int height) : Figure("RECT"), width(width), height(height) {}
  
  string Name() const override {
      return name;
  }
  
  double Perimeter() const override {
      return 2 * (width + height);
  }
  
  double Area() const override {
      return width * height;
  }
 
 private:
  uint16_t width, height;
};

class Circle : public Figure {
 public:
  string Name() const override {
      return name;
  }
  
  Circle(int r) : Figure("CIRCLE"), r(r) {}
  
  double Perimeter() const override {
      return 2 * PI * r;
  }
  
  double Area() const override {
      return PI * r * r;
  }
 
 private:
  uint16_t r;
};

enum Figure_type {
  TRIANGLE,
  RECT,
  CIRCLE
};

istream &operator>>(istream &in, Figure_type &type) {
    string str_type;
    in >> str_type;
    if (str_type == "TRIANGLE") {
        type = Figure_type::TRIANGLE;
    } else if (str_type == "RECT") {
        type = Figure_type::RECT;
    } else if (str_type == "CIRCLE") {
        type = Figure_type::CIRCLE;
    } else {
        throw logic_error("unknown figure: " + str_type);
    }
    return in;
}

shared_ptr<Figure> CreateFigure(istream &in) {
    Figure_type type;
    in >> type;
    
    switch (type) {
        case Figure_type::TRIANGLE : {
            int a, b, c;
            in >> a >> b >> c;
            return make_shared<Triangle>(a, b, c);
            break;
        }
        case Figure_type::RECT : {
            int width, height;
            in >> width >> height;
            return make_shared<Rect>(width, height);
            break;
        }
        case Figure_type::CIRCLE : {
            int r;
            in >> r;
            return make_shared<Circle>(r);
            break;
        }
        default: {
            throw logic_error("wtf");
            break;
        }
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);
        
        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}


// ==========================================
