//
// Created by Addmin on 21.12.2020.
//
//#pragma once

#include <cstdlib>
#include <utility>

template<class T>
class SimpleVector {
 public:
  SimpleVector() = default;
  SimpleVector(const SimpleVector &);
  SimpleVector(SimpleVector &&) noexcept;
  explicit SimpleVector(size_t);
  
  SimpleVector &operator=(SimpleVector &&) noexcept;
  SimpleVector &operator=(const SimpleVector &);
  
  T *begin();
  const T *begin() const;
  T *end();
  const T *end() const;
  
  T &operator[](size_t);
  
  void PushBack(T &&);
  void PushBack(const T &);
  
  [[nodiscard]] size_t Size() const;
  [[nodiscard]] size_t Capacity() const;
  
  virtual ~SimpleVector();
 
 private:
  T *data_{};
  size_t size_{}, capacity_{};
};

template<class T>
SimpleVector<T>::SimpleVector(const SimpleVector &other)
    : data_(new T[other.capacity_]), size_(0), capacity_(other.capacity_) {
    for (const auto &item : other) {
        PushBack(item);
    }
}

template<class T>
SimpleVector<T>::SimpleVector(SimpleVector &&other) noexcept
    :data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) :data_(new T[size]{}), size_(size), capacity_(size) {}

template<class T>
SimpleVector<T> &SimpleVector<T>::operator=(SimpleVector &&other) noexcept {
    if (this == &other) { return *this; }
    
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.size_ = other.capacity_ = 0;
    
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

template<class T>
SimpleVector<T> &SimpleVector<T>::operator=(const SimpleVector &other) {
    if (this == &other) { return *this; }
    
    *this = SimpleVector(other);
    return *this;
}

template<typename T>
T &SimpleVector<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
T *SimpleVector<T>::begin() {
    return data_;
}

template<class T>
const T *SimpleVector<T>::begin() const {
    return data_;
}

template<typename T>
T *SimpleVector<T>::end() {
    return data_ + size_;
}

template<class T>
const T *SimpleVector<T>::end() const {
    return data_ + size_;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return size_;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}

template<typename T>
void SimpleVector<T>::PushBack(T &&value) {
    if (Capacity() == 0) {
        capacity_ = 1;
        data_ = new T[capacity_];
    } else if (Size() == Capacity()) {
        capacity_ *= 2;
        T *new_data = new T[capacity_];
        for (std::size_t i = 0; i < Size(); ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
    }
    
    data_[size_++] = std::move(value);
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    PushBack(T(value));
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data_;
}

