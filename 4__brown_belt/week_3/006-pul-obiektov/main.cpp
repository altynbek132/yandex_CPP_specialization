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
    T* Allocate();
    T* TryAllocate();

    void Deallocate(T* object);

    ~ObjectPool();

   private:
    // Добавьте сюда поля
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
