#pragma once

#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
   public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) : data(new T[size]), size(size), capacity(size) {}
    ~SimpleVector() { delete[] data; }

    T& operator[](size_t index) { return data[index]; }

    T* begin() { return data; }
    T* end() { return data + size; }

    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }
    void PushBack(const T& value) {
        if (Size() >= Capacity()) {
            size_t new_capacity = 1;
            if (capacity != 0)
                new_capacity = capacity * 2;

            auto new_data = new T[new_capacity];
            copy(begin(), end(), new_data);
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

   private:
    T* data = nullptr;
    size_t size = 0, capacity = 0;
};
