// #include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
   private:
    T* data_ = nullptr;

   public:
    UniquePtr() = default;
    explicit UniquePtr(T* ptr) : data_(ptr) {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(nullptr_t) {
        Reset(nullptr);
        return *this;
    }

    UniquePtr(UniquePtr&& other) noexcept { data_ = other.Release(); }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        Reset(other.Release());
        return *this;
    }

    ~UniquePtr() { Reset(nullptr); }

    T& operator*() const { return *Get(); }

    T* operator->() const { return Get(); }

    T* Release() {
        auto res = data_;
        data_ = nullptr;
        return res;
    }

    void Reset(T* ptr) {
        delete data_;
        data_ = ptr;
    }

    void Swap(UniquePtr& other) { swap(other.data_, data_); }

    T* Get() const { return data_; }
};

struct Item {
    static int counter;
    int value;
    Item(int v = 0) : value(v) { ++counter; }
    Item(const Item& other) : value(other.value) { ++counter; }
    ~Item() { --counter; }
};

int Item::counter = 0;

void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
}
