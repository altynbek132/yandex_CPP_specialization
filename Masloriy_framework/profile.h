#include "glue.h"
#pragma once

#include <chrono>
#include <iostream>
#include <string>

//-------------------------------------------------------------------------------------------------
class LogDuration {
   public:
    explicit LogDuration(const std::string& msg = "")
        : message(msg + " | "), start(std::chrono::steady_clock::now()) {}

    ~LogDuration() {
        auto finish = std::chrono::steady_clock::now();
        auto duration = finish - start;

        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        duration -= milliseconds;
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
        duration -= microseconds;
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        duration -= nanoseconds;

        std::cerr << "================================================================================"
                  << std::endl;
        std::cerr << message << std::endl;
        std::cerr << seconds.count() << " sec, " << std::endl;
        std::cerr << milliseconds.count() << " mils " << std::endl;
        std::cerr << microseconds.count() << " mics " << std::endl;
        std::cerr << nanoseconds.count() << " nans " << std::endl;
        std::cerr << "================================================================================"
                  << std::endl;
    }

   private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};
//-------------------------------------------------------------------------------------------------
#define UNIQ_SS GLUE(_profile_uniq_ss, __LINE__)
#define UNIQ_LOG_DURATION GLUE(_profile_uniq_log_duration, __LINE__)
#define LOG_DURATION(message)                                                     \
    stringstream UNIQ_SS;                                                         \
    UNIQ_SS << (message) << " | " << endl << __FILE__ << ":" << __LINE__ << endl; \
    LogDuration UNIQ_LOG_DURATION{UNIQ_SS.str()};

//-------------------------------------------------------------------------------------------------
