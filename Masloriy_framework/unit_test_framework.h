//
// Created by Addmin on 10.12.2020.
//

#pragma once

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <fstream>

#include "utilities.h"

#define AssertEqual(actual, expected)       _AssertEqual(actual, expected, __FILE__, __LINE__)
#define Assert(statement)       _Assert(statement, __FILE__, __LINE__)

template<class A, class B>
void _AssertEqual(const A &actual, const B &expected, const std::string &file, int line) {
    if (actual == expected) {
        return;
    }
    
    std::ifstream in(file);
    int line_ = line;
    while (--line_) {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string error_line;
    getline(in, error_line);
    in.close();
    
    std::stringstream error;
    error << "Assertion error at:" << std::endl << file << ":" << line << ": " << std::endl;
    error << error_line << std::endl;
    error << "Expected:" << std::endl << expected << std::endl;
    error << "Actual:" << std::endl << actual << std::endl;
    throw std::runtime_error(error.str());
}

void _Assert(const bool &statement, const std::string &file, int line);


class TestRunner {
 public:
  explicit TestRunner(std::string description);
  
  template<class Func>
  void RunTest(Func &test, const std::string &test_name) {
      try {
          test();
      } catch (std::exception &ex) {
          std::cerr << "test case \"" << test_name << "\" failed" << std::endl;
          std::cerr << ex.what() << std::endl;
          fail_count++;
      } catch (...) {
          std::cerr << "Unknown exception caught" << std::endl;
          fail_count++;
      }
  }
  
  virtual ~TestRunner();
 
 private:
  std::string description;
  size_t fail_count;
};
