//
// Created by Addmin on 10.12.2020.
//

#include "tests.h"
#include "phone_number.h"

struct number {
  std::string country, city, local, international;
  
  number(const std::string &country, const std::string &city, const std::string &local)
      : country(country), city(city), local(local) {
      std::stringstream ss;
      ss << "+" << country << "-" << city << "-" << local;
      international = ss.str();
  }
};

void basic_test() {
    std::mt19937 gen;
    std::uniform_real_distribution<> unifdouble(-10, 10);
    std::uniform_int_distribution<int> unifint(-10, 10);
    
    std::vector<number> valid_numbers = {
        {"7", "495", "111-22-33",},
        {"7", "495", "1112233",},
        {"323", "22", "460002",},
        {"1", "2", "coursera-cpp",}
    };
    
    for (auto &num : valid_numbers) {
        PhoneNumber ph(num.international);
        AssertEqual(ph.GetInternationalNumber(), num.international);
        AssertEqual(ph.GetCountryCode(), num.country);
        AssertEqual(ph.GetCityCode(), num.city);
        AssertEqual(ph.GetLocalNumber(), num.local);
    }
    
    
    std::vector<std::string> invalid_numbers = {
        "1-2-333",
        "+7-1233"
    };
    
    for (auto &num : invalid_numbers) {
        try {
            PhoneNumber ph(num);
            Assert(false);
        } catch (std::invalid_argument &ex) {
        } catch (exception &ex) {
            Assert(false);
        }
    }

//    +7-495-111-22-33
//    +7-495-1112233
//    +323-22-460002
//    +1-2-coursera-cpp
//    1-2-333 - некорректный номер - не начинается на '+'
//    +7-1233 - некорректный номер - есть только код страны и города
}


// this function is entry for testing
void TestAll() {
    {
        TestRunner tr("test1");
        tr.RunTest(basic_test, "basic test");
    }
}
