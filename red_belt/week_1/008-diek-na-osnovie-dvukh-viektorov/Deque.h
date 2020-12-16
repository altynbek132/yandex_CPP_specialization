//
// Created by Addmin on 16.12.2020.
//

#pragma once
#include <cstdlib>
#include <vector>

using namespace std;

template<class T>
class Deque {
 public:
  Deque();
  bool Empty() const;
  size_t Size() const;
  T &operator[](size_t index);
  const T &operator[](size_t index) const;
  
  //  out_of_range
  T &At(size_t index);
  const T &At(size_t index) const;
  
  T &Front();
  const T &Front() const;
  T &Back();
  const T &Back() const;
  
  void PushFront(const T &val);
  void PushBack(const T &val);
 private:
  vector<T> front, back;
};

// =================================
// =================================
// =================================

template<class T>
Deque<T>::Deque() = default;

template<class T>
bool Deque<T>::Empty() const {
    return front.empty() && back.empty();
}

template<class T>
size_t Deque<T>::Size() const {
    return front.size() + back.size();
}

template<class T>
T &Deque<T>::At(size_t index) {
    if (index < front.size()) {
        return front.at(front.size() - 1 - index);
    }
    return back.at(index - front.size());
}

template<class T>
const T &Deque<T>::At(size_t index) const {
    if (index < front.size()) {
        return front.at(front.size() - 1 - index);
    }
    return back.at(index - front.size());
}

template<class T>
T &Deque<T>::operator[](size_t index) {
    return At(index);
}

template<class T>
const T &Deque<T>::operator[](size_t index) const {
    return At(index);
}

template<class T>
T &Deque<T>::Front() {
    return At(0);
}

template<class T>
const T &Deque<T>::Front() const {
    return At(0);
}

template<class T>
T &Deque<T>::Back() {
    return At(Size() - 1);
}

template<class T>
const T &Deque<T>::Back() const {
    return At(Size() - 1);
}

template<class T>
void Deque<T>::PushFront(const T &val) {
    front.push_back(val);
}

template<class T>
void Deque<T>::PushBack(const T &val) {
    back.push_back(val);
}
