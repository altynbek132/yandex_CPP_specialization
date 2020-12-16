#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================


#include "test_runner.h"
#include <sstream>
#include <string>

using namespace std;

class Logger {
 public:
  explicit Logger(ostream &output_stream) : os(output_stream) {
  }
  
  void SetLogLine(bool value) { log_line = value; }
  
  void SetLogFile(bool value) { log_file = value; }
  
  void Log(const string &message) {
      if (log_file && log_line) {
          os << file << ":" << line << " ";
      } else if (log_file) {
          os << file << " ";
      } else if (log_line) {
          os << "Line " << line << " ";
      }
      os << message << std::endl;
  }
  
  void SetLine(int line) {
      Logger::line = line;
  }
  
  void SetFile(const string &file) {
      Logger::file = file;
  }
 
 private:
  ostream &os;
  bool log_line = false;
  bool log_file = false;
  int line;
  std::string file;
};

#define LOG(logger, message) {      \
    logger.SetFile(__FILE__);       \
    logger.SetLine(__LINE__);       \
    logger.Log(message);            \
}

void TestLog() {
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"
    
    ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");
    
    l.SetLogFile(true);
    LOG(l, "hello");
    
    l.SetLogLine(true);
    LOG(l, "hello");
    
    l.SetLogFile(false);
    LOG(l, "hello");
    
    string expected = "hello\n";
    expected += "logger.cpp hello\n";
    expected += "logger.cpp:10 hello\n";
    expected += "Line 13 hello\n";
    ASSERT_EQUAL(logs.str(), expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLog);
}

// ==========================================
