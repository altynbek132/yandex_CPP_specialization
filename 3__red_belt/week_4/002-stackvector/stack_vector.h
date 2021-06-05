#pragma once

#include <array>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class StackVector {
   public:
    explicit StackVector(size_t a_size = 0);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    typename array<T, N>::iterator begin();
    typename array<T, N>::iterator end();
    typename array<T, N>::const_iterator begin() const;
    typename array<T, N>::const_iterator end() const;

    size_t Size() const;
    size_t Capacity() const;

    void PushBack(const T& value);
    T PopBack();

   private:
    array<T, N> data;
    size_t size;
};

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) : size(a_size) {
    if (size > N) {
        throw invalid_argument("size is more than capacity");
    }
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index) {
    return data[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const {
    return data[index];
}

template <typename T, size_t N>
typename array<T, N>::iterator StackVector<T, N>::begin() {
    return data.begin();
}

template <typename T, size_t N>
typename array<T, N>::iterator StackVector<T, N>::end() {
    return data.begin() + Size();
}

template <typename T, size_t N>
typename array<T, N>::const_iterator StackVector<T, N>::begin() const {
    return data.begin();
}

template <typename T, size_t N>
typename array<T, N>::const_iterator StackVector<T, N>::end() const {
    return data.begin() + Size();
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const {
    return size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
    return N;
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value) {
    if (Size() == Capacity()) {
        throw overflow_error("");
    }
    data[size++] = value;
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack() {
    if (Size() == 0) {
        throw underflow_error("");
    }
    return data[--size];
}
