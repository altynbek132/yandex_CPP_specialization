#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template<class T>
class ObjectPool {
 public:
  T *Allocate();
  T *TryAllocate();
  
  void Deallocate(T *object);
  
  ~ObjectPool();
 
 private:
  set<T *> allocated;
  deque<T *> deallocated;
};

template<class T>
T *ObjectPool<T>::Allocate() {
    if (deallocated.empty()) {
        auto p = new T;
        allocated.insert(p);
        return p;
    }
    auto p = deallocated.front();
    allocated.insert(p);
    deallocated.pop_front();
    return p;
}

template<class T>
T *ObjectPool<T>::TryAllocate() {
    if (deallocated.empty()) {
        return nullptr;
    }
    return Allocate();
}

template<class T>
void ObjectPool<T>::Deallocate(T *object) {
    auto it = allocated.find(object);
    if (it == allocated.end()) {
        throw std::invalid_argument("object is not stored in allocated set");
    }
    deallocated.push_back(*it);
    allocated.erase(it);
}

template<class T>
ObjectPool<T>::~ObjectPool() {
    std::for_each(allocated.begin(), allocated.end(), std::default_delete<T>());
    std::for_each(deallocated.begin(), deallocated.end(), std::default_delete<T>());
}

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
// ==========================================
