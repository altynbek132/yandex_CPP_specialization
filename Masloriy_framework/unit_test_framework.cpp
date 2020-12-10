#include "unit_test_framework.h"
//
//template<class A, class B>
//void _AssertEqual(const A &actual, const B &expected, const std::string &file, int line) {
//    if (actual == expected) {
//        return;
//    }
//
//    std::ifstream in(file);
//    int line_ = line;
//    while (--line_) {
//        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//    std::string error_line;
//    getline(in, error_line);
//    in.close();
//
//    std::stringstream error;
//    error << "Assertion error at line " << line << ": " << std::endl;
//    error << error_line << std::endl;
//    error << "Expected:" << std::endl << expected << std::endl;
//    error << "Actual:" << std::endl << actual << std::endl;
//    throw std::runtime_error(error.str());
//}

void _Assert(const bool &statement, const std::string &file, int line) {
    _AssertEqual(statement, true, file, line);
}



TestRunner::TestRunner(std::string description) : description(std::move(description)), fail_count(0) {}

//template<class Func>
//void TestRunner::RunTest(Func &test, const std::string &test_name) {
//    try {
//        test();
//    } catch (std::exception &ex) {
//        std::cerr << "test case \"" << test_name << "\" failed" << std::endl;
//        std::cerr << ex.what() << std::endl;
//        fail_count++;
//    } catch (...) {
//        std::cerr << "Unknown exception caught" << std::endl;
//        fail_count++;
//    }
//}

TestRunner::~TestRunner() {
    if (fail_count == 0) {
        std::cerr << "Block test \"" << description << "\" finished successfully!" << std::endl;
    } else {
        std::cerr << "Block test \"" << description << "\" finished with " << fail_count << " errors!" << std::endl;
        exit(1);
    }
}
 

