#pragma once
#include <mutex>
#include <ostream>

using namespace std;
template <typename T>
class Synchronized {
   public:
    explicit Synchronized(T initial = T()) : value(move(initial)) {}

    struct Access {
        T& ref_to_value;
        lock_guard<mutex> g;
    };

    Access GetAccess() { return {value, lock_guard(m)}; }
    // const T& GetAccess() const { return value; }

   private:
    T value;
    mutex m;
};
