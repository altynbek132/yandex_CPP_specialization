#ifdef MASLO

#include "tests.h"
#include "solution.h"
#include <bits/stdc++.h>


#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>

using namespace std;


void TestUniqueMax() {
    auto IsEven = [](int x) {
      return x % 2 == 0;
    };
    
    const list<int> hill{2, 4, 8, 9, 6, 4, 2};
    auto max_iterator = hill.begin();
    advance(max_iterator, 2);
    
    vector<int> numbers(10);
    iota(numbers.begin(), numbers.end(), 1);
    
    /*
      Мы не используем AssertEqual, потому что для итераторов
      отсутствует перегрузка оператора вывода в поток ostream.
      Разыменование здесь также недопустимо, так как оно может повлечь
      неопределенное поведение, если функция max_element_if, к примеру,
      вернула итератор, указывающий на конец контейнера.
    */
    Assert(
        max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end()
    );
    Assert(
        max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator
    );
}

void TestSeveralMax() {
    struct IsCapitalized {
      bool operator()(const string &s) {
          return !s.empty() && isupper(s.front());
      }
    };
    
    const forward_list<string> text{"One", "two", "Three", "One", "Two",
                                    "Three", "one", "Two", "three"};
    auto max_iterator = text.begin();
    advance(max_iterator, 4);
    
    Assert(
        max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator
    );
}

void TestNoMax() {
    const vector<int> empty;
    const string str = "Non-empty string";
    
    auto AlwaysTrue = [](int) {
      return true;
    };
    Assert(
        max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end()
    );
    
    auto AlwaysFalse = [](char) {
      return false;
    };
    Assert(
        max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end()
    );
}



string gen_random(const int len) {
    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    tmp_s.reserve(len);
    
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}


void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> dd(-10, 10);
    std::uniform_int_distribution<int> ii(-10, 10);
}

// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
        tr.RunTest(TestUniqueMax, "TestUniqueMax");
        tr.RunTest(TestSeveralMax, "TestSeveralMax");
        tr.RunTest(TestNoMax, "TestNoMax");
    }
}

#endif
