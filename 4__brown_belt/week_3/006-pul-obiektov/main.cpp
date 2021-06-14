#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
using namespace std;

template <class T>
class ObjectPool {
   public:
    T* Allocate() {
        if (deallocated.empty()) {
            deallocated.push(new T);
        }
        auto ret = deallocated.front();
        deallocated.pop();
        allocated.insert(ret);
        return ret;
    }
    T* TryAllocate() {
        if (deallocated.empty())
            return nullptr;
        return Allocate();
    }

    void Deallocate(T* object) {
        auto it = allocated.find(object);
        if (it == allocated.end())
            throw invalid_argument("chotam?");
        allocated.erase(it);
        deallocated.push(object);
    }

    ~ObjectPool() {
        for (auto& obj : allocated) {
            delete obj;
        }
        while (!deallocated.empty()) {
            auto obj = deallocated.front();
            deallocated.pop();
            delete obj;
        }
    }

   private:
    set<T*> allocated;
    queue<T*> deallocated;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
