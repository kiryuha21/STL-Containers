// Copyright 2023 School-21

#ifndef SRC_SOURCE_VECTOR_H_
#define SRC_SOURCE_VECTOR_H_

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "container.h"

namespace s21 {

template <class T>
class vector : public container<T> {
 public:
  // Vector Member type
  using value_type = typename container<T>::value_type;
  using reference = typename container<T>::reference;
  using const_reference = typename container<T>::const_reference;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = typename container<T>::size_type;

  // Vector Member functions
  vector() noexcept = default;
  vector(const size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector() noexcept override;
  vector &operator=(const vector &v);
  vector &operator=(vector &&v) noexcept;

  // Vector Element access
  reference at(const size_type pos) const;
  reference operator[](const size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data() const;

  // Vector Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;

  // Vector Capacity
  [[nodiscard]] bool empty() const noexcept override;
  [[nodiscard]] size_type size() const noexcept override;
  [[nodiscard]] size_type max_size() const noexcept;
  void reserve(const size_type size);
  [[nodiscard]] size_type capacity() const noexcept;
  void shrink_to_fit();

  // Vector Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept;

 private:
  // Vector Attributes
  value_type *memory_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  // Max size
  static constexpr size_type kMaxSize = size_type(-1) / sizeof(value_type);

  // Helpers
  void allocate_memory(const size_type n);
  void resize(const size_type n);
  void recap(const size_type n);
  [[nodiscard]] size_type calculate_capacity(
      const size_type size) const noexcept;
  void shift_left(const size_type shift_after, const size_type shift_on);
  void shift_right(const size_type shift_after, const size_type shift_on);
};

// Helpers
template <class T>
void vector<T>::allocate_memory(const size_type n) {
  delete[] memory_;

  if (n != 0) {
    try {
      memory_ = new value_type[n];
    } catch (const std::bad_alloc &exc) {
      throw std::out_of_range("Alloc error in allocate_memory");
    }
  }

  capacity_ = n;
}

template <class T>
void vector<T>::resize(const size_type n) {
  if (n <= capacity_) {
    size_ = n;
    return;
  }

  if (empty()) {
    *this = vector(n);
    return;
  }

  recap(calculate_capacity(n));
  size_ = n;
}

template <class T>
void vector<T>::recap(const size_type n) {
  vector<value_type> copy(*this);
  allocate_memory(n);
  std::copy(copy.begin(), copy.begin() + std::min(copy.size_, n), begin());
}

template <class T>
typename vector<T>::size_type vector<T>::calculate_capacity(
    const size_type size) const noexcept {
  size_type res = std::max(capacity_, size_type(1));
  while (res < size) {
    res *= 2;
  }

  return res;
}

template <class T>
void vector<T>::shift_right(const size_type shift_after,
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
void vector<T>::shift_left(const size_type shift_after,
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
vector<T>::vector(const size_type n) : size_(n) {
  allocate_memory(n);
  std::fill(begin(), end(), value_type());
}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()) {
  allocate_memory(items.size());
  std::copy(items.begin(), items.end(), memory_);
}

template <class T>
vector<T> &vector<T>::operator=(const vector<T> &v) {
  if (this == &v) {
    return *this;
  }

  allocate_memory(v.capacity_);
  size_ = v.size_;
  std::copy(v.begin(), v.end(), begin());

  return *this;
}

template <class T>
vector<T>::vector(const vector &v) {
  *this = v;
}

template <class T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
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
vector<T>::vector(vector &&v) noexcept {
  *this = std::move(v);
}

template <class T>
vector<T>::~vector() noexcept {
  delete[] memory_;
}

// Vector Element access
template <class T>
typename vector<T>::reference vector<T>::at(const size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Wrong position for at");
  } else if (empty()) {
    throw std::out_of_range("Taking at of empty Vector");
  }

  return memory_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](const size_type pos) const {
  return at(pos);
}

template <class T>
typename vector<T>::const_reference vector<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Taking front of empty Vector");
  }
  return memory_[0];
}

template <class T>
typename vector<T>::const_reference vector<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Taking back of empty Vector");
  }
  return memory_[size_ - 1];
}

template <class T>
typename vector<T>::iterator vector<T>::data() const {
  return memory_;
}

// Vector Iterators
template <class T>
typename vector<T>::iterator vector<T>::begin() const noexcept {
  return memory_;
}

template <class T>
typename vector<T>::iterator vector<T>::end() const noexcept {
  if (memory_ == nullptr) {
    return nullptr;
  }

  return memory_ + size_;
}

// Vector Capacity
template <class T>
bool vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return this->kMaxSize;
}

template <class T>
void vector<T>::shrink_to_fit() {
  recap(size_);
}

template <class T>
void vector<T>::reserve(const size_type size) {
  if (size > capacity_) {
    recap(size);
  }
}

// Vector Modifiers
template <class T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
void vector<T>::swap(vector<T> &other) noexcept {
  std::swap(*this, other);
}

template <class T>
void vector<T>::push_back(const_reference value) {
  resize(size_ + 1);
  *(end() - 1) = value;
}

template <class T>
void vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Pop back of empty vector");
  }
  resize(size_ - 1);
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
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
void vector<T>::erase(iterator pos) {
  if (empty()) {
    throw std::out_of_range("Erase of empty vector");
  } else if (pos >= end() || pos < begin()) {
    throw std::out_of_range("Bad erase place");
  }
  auto res_position = size_type(pos - memory_);
  shift_left(res_position, 1);
}

}  // namespace s21

#endif  // SRC_SOURCE_VECTOR_H_
