// Copyright 2023 School-21

#include "../include/Vector.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace s21 {

// Helpers
template <class T>
void Vector<T>::allocate_memory(const size_type n) {
  if (n > kMaxSize) {
    throw std::out_of_range("Vector size must be in (0; 2^61 - 1]");
  }

  delete[] memory_;

  if (n != 0) {
    try {
      memory_ = new value_type[n];
    } catch (const std::bad_alloc& exc) {
      throw std::out_of_range("Alloc error in allocate_memory");
    }
  }

  capacity_ = n;
}

template <class T>
void Vector<T>::resize(const size_type n) {
  if (n <= capacity_) {
    size_ = n;
    return;
  }

  if (empty()) {
    *this = Vector(n);
    return;
  }

  recap(calculate_capacity(n));
  size_ = n;
}

template <class T>
void Vector<T>::recap(const size_type n) {
  Vector<value_type> copy(*this);
  allocate_memory(n);
  std::copy(copy.begin(), copy.begin() + std::min(copy.size_, n), begin());
}

template <class T>
typename Vector<T>::size_type Vector<T>::calculate_capacity(
    const size_type size) const noexcept {
  size_type res = std::max(capacity_, size_type(1));
  while (res < size) {
    res *= 2;
  }

  return res;
}

template <class T>
void Vector<T>::shift_right(const size_type shift_after,
                            const size_type shift_on) {
  resize(size_ + shift_on);
  for (size_type i = size_ - 1; i >= shift_after + shift_on; --i) {
    memory_[i] = memory_[i - shift_on];
  }
  for (size_type i = shift_after + shift_on - 1; i > shift_after; --i) {
    memory_[i] = value_type();
  }
}

template <class T>
void Vector<T>::shift_left(const size_type shift_after,
                           const size_type shift_on) {
  if (size_ < shift_on + shift_after) {
    throw std::out_of_range("Shift left on too big value");
  }

  for (size_type i = shift_after; i < size_ - shift_on; ++i) {
    memory_[i] = memory_[i + shift_on];
  }
  resize(size_ - shift_on);
}

// Vector Member type
template <class T>
Vector<T>::Vector(const size_type n) : size_(n) {
  allocate_memory(n);
  std::fill(begin(), end(), value_type());
}

template <class T>
Vector<T>::Vector(std::initializer_list<value_type> const& items)
    : size_(items.size()) {
  allocate_memory(items.size());
  std::copy(items.begin(), items.end(), memory_);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
  if (this == &v) {
    return *this;
  }

  allocate_memory(v.capacity_);
  size_ = v.size_;
  std::copy(v.begin(), v.end(), begin());

  return *this;
}

template <class T>
Vector<T>::Vector(const Vector& v) {
  *this = v;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept {
  if (this == &v) {
    return *this;
  }

  delete[] memory_;

  memory_ = std::exchange(v.memory_, nullptr);
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);

  return *this;
}

template <class T>
Vector<T>::Vector(Vector&& v) noexcept {
  *this = std::move(v);
}

template <class T>
Vector<T>::~Vector() noexcept {
  delete[] memory_;
}

// Vector Element access
template <class T>
typename Vector<T>::reference Vector<T>::at(const size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Wrong position for at");
  } else if (empty()) {
    throw std::out_of_range("Taking at of empty Vector");
  }

  return memory_[pos];
}

template <class T>
typename Vector<T>::reference Vector<T>::operator[](const size_type pos) const {
  return at(pos);
}

template <class T>
typename Vector<T>::const_reference Vector<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Taking front of empty Vector");
  }
  return memory_[0];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Taking back of empty Vector");
  }
  return memory_[size_ - 1];
}

template <class T>
typename Vector<T>::iterator Vector<T>::data() const {
  return memory_;
}

// Vector Iterators
template <class T>
typename Vector<T>::iterator Vector<T>::begin() const noexcept {
  return memory_;
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() const noexcept {
  if (memory_ == nullptr) {
    return nullptr;
  }

  return memory_ + size_;
}

// Vector Capacity
template <class T>
bool Vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
  return size_;
}

template <class T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
  return kMaxSize;  // TODO: CHECK
}

template <class T>
void Vector<T>::shrink_to_fit() {
  recap(size_);
}

template <class T>
void Vector<T>::reserve(const size_type size) {
  if (size > capacity_) {
    recap(size);
  }
}

// Vector Modifiers
template <class T>
void Vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
void Vector<T>::swap(Vector<T>& other) noexcept {
  std::swap(*this, other);
}

template <class T>
void Vector<T>::push_back(const_reference value) {
  resize(size_ + 1);
  *(end() - 1) = value;
}

template <class T>
void Vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Pop back of empty vector");
  }
  resize(size_ - 1);
}

template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  auto res_position = size_type(pos - begin());
  if ((pos >= end() || pos < begin()) && !empty()) {
    throw std::out_of_range("Bad insert place");
  }
  shift_right(res_position, 1);
  *(memory_ + res_position) = value;
  return memory_ + res_position;
}

template <class T>
void Vector<T>::erase(iterator pos) {
  if (empty()) {
    throw std::out_of_range("Erase of empty vector");
  } else if (pos >= end() || pos < begin()) {
    throw std::out_of_range("Bad erase place");
  }
  auto res_position = size_type(pos - memory_);
  shift_left(res_position, 1);
}

}  // namespace s21
