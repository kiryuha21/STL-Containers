#include "../include/vector.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace s21 {

// Helpers
template <class T>
void vector<T>::allocate_memory(const size_type n) {
  if (n <= 0) {
    throw std::out_of_range("Vector size must be >= 0");
  }

  capacity_ = requirement_capacity(n);

  try {
    it_begin_ = new value_type[capacity_];
  } catch (const std::bad_alloc& exc) {
    capacity_ = 0;
    throw std::out_of_range("Alloc error in allocate_memory");
  }

  size_ = n;
  it_end_ = it_begin_ + n + 1;
}

template <class T>
void vector<T>::resize(const size_type n) {
  if (this->empty() || capacity_ == requirement_capacity(n)) {
    return;
  }

  vector<value_type> new_vector(n);
  std::fill(new_vector.it_begin_, new_vector.it_end_, it_begin_);
  *this = std::move(new_vector);
}

template <class T>
typename vector<T>::size_type vector<T>::requirement_capacity(
    const size_type size) const noexcept {
  if (capacity_ == 0) {
    return 0;
  }

  auto res =
      size_type(pow(2, double(size_type(std::log(size) / std::log(2))) + 1));

  return res;
}

// Vector Member type
template <class T>
vector<T>::vector(const size_type n) {
  allocate_memory(n);
}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const& items) {
  allocate_memory(items.size());
  std::fill(it_begin_, it_end_, items.begin());
}

template <class T>
vector<T>& vector<T>::operator=(const vector<T>& v) noexcept {
  if (this == v) {
    return *this;
  }

  allocate_memory(v.size_);
  std::fill(it_begin_, it_end_, v.begin());
  return *this;
}

template <class T>
vector<T>::vector(const vector& v) noexcept {
  *this = v;
}

template <class T>
vector<T>& vector<T>::operator=(vector<T>&& v) noexcept {
  if (*this == v) {
    return *this;
  }

  delete[] it_begin_;

  it_begin_ = std::exchange(v.it_begin_, nullptr);
  it_end_ = std::exchange(v.it_end_, nullptr);
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);

  return *this;
}

template <class T>
vector<T>::vector(vector&& v) noexcept {
  *this == std::move(v);
}

template <class T>
vector<T>::~vector() noexcept {
  this->clear();
}

// Vector Element access
template <class T>
typename vector<T>::reference vector<T>::at(const size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Wrong position for at");
  } else if (this->empty()) {
    throw std::out_of_range("Taking at of empty vector");
  }

  return it_begin_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](const size_type pos) const {
  return this->at(pos);
}

template <class T>
typename vector<T>::const_reference vector<T>::front() const {
  if (this->empty()) {
    throw std::out_of_range("Taking front of empty vector");
  }
  return this->at(0);
}

template <class T>
typename vector<T>::const_reference vector<T>::back() const {
  if (this->empty()) {
    throw std::out_of_range("Taking back of empty vector");
  }
  return *(it_end_ - 1);
}

template <class T>
typename vector<T>::iterator vector<T>::data() const {
  if (this->empty()) {
    throw std::out_of_range("Taking data of empty vector");
  }
  return it_begin_;
}

// Vector Iterators
template <class T>
typename vector<T>::iterator vector<T>::begin() const {
  if (this->empty()) {
    throw std::out_of_range("Taking begin of empty vector");
  }
  return it_begin_;
}

template <class T>
typename vector<T>::iterator vector<T>::end() const {
  if (this->empty()) {
    throw std::out_of_range("Taking end of empty vector");
  }
  return it_end_;
}

// Vector Capacity
template <class T>
bool vector<T>::empty() const {
  return it_begin_ == nullptr;
}

template <class T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() const {
  return this->capacity();  // TODO: not right 100%
}

template <class T>
void vector<T>::shrink_to_fit() {
  this->resize(size_);  // TODO: maybe cap should be = size
}

template <class T>
void vector<T>::reserve(const size_type size) {
  if (size <= capacity_) {
    return;
  }

  this->resize(size);
}

// Vector Modifiers
template <class T>
void vector<T>::clear() {
  delete[] it_begin_;
  it_begin_ = it_end_ = nullptr;
  size_ = capacity_ = 0;
}

template <class T>
void vector<T>::swap(vector<T>& other) {
  vector temp = std::move(other);
  other = std::move(*this);
  *this = std::move(temp);
}

}  // namespace s21