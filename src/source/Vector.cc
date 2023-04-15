#include "../include/Vector.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace s21 {

// Helpers
template <typename T>
void Vector<T>::allocate_memory(const size_type n) {
  if (n > kMaxSize) {
    throw std::out_of_range("Vector size must be in [0; 2^61 - 1]");
  }

  capacity_ = calculate_capacity(n);

  try {
    it_begin_ = new value_type[capacity_];
  } catch (const std::bad_alloc& exc) {
    capacity_ = 0;
    throw std::out_of_range("Alloc error in allocate_memory");
  }

  size_ = n;
  it_end_ = it_begin_ + n - 1;
  std::fill(begin(), end(), value_type());
}

template <typename T>
void Vector<T>::resize(const size_type n) {
  if (capacity_ == calculate_capacity(n)) {
    return;
  }

  Vector<value_type> new_vector(n);
  *this = std::move(new_vector);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::calculate_capacity(
    const size_type size) const noexcept {
  if (size == 0) {
    return 0;
  }

  auto res =
      size_type(pow(2, double(size_type(std::log(size) / std::log(2))) + 1));

  return res;
}

template <typename T>
void Vector<T>::shift_right(iterator shift_from, const size_type shift_on) {
  auto shift_count = it_end_ - shift_from;
  resize(size_ + shift_on);
  std::copy(shift_from, shift_from + shift_count + 1, shift_from + shift_on);
}

template <typename T>
void Vector<T>::shift_left(iterator shift_from, const size_type shift_on) {
  if (it_begin_ + shift_on < shift_from) {
    throw std::out_of_range("Shift left on too big value");
  }

  auto shift_count = shift_from - it_begin_;
  std::copy(shift_from, shift_from + shift_count + 1, shift_from - shift_on);
  resize(size_ - shift_on);
}

// Vector Member type
template <typename T>
Vector<T>::Vector(const size_type n) {
  allocate_memory(n);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const& items) {
  allocate_memory(items.size());
  std::copy(items.begin(), items.end(), it_begin_);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
  if (this == &v) {
    return *this;
  }

  allocate_memory(v.size_);
  std::copy(v.begin(), v.end(), begin());
  return *this;
}

template <typename T>
Vector<T>::Vector(const Vector& v) noexcept {
  *this = v;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept {
  if (this == &v) {
    return *this;
  }

  delete[] it_begin_;

  it_begin_ = std::exchange(v.it_begin_, nullptr);
  it_end_ = std::exchange(v.it_end_, nullptr);
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);

  return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& v) noexcept {
  *this = std::move(v);
}

template <typename T>
Vector<T>::~Vector() noexcept {
  clear();
}

// Vector Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(const size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Wrong position for at");
  } else if (empty()) {
    throw std::out_of_range("Taking at of empty Vector");
  }

  return it_begin_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](const size_type pos) const {
  return at(pos);
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Taking front of empty Vector");
  }
  return at(0);
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Taking back of empty Vector");
  }
  return *it_end_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::data() const {
  if (empty()) {
    throw std::out_of_range("Taking data of empty Vector");
  }
  return it_begin_;
}

// Vector Iterators
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
  if (empty()) {
    throw std::out_of_range("Taking begin of empty Vector");
  }
  return it_begin_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const {
  if (empty()) {
    throw std::out_of_range("Taking end of empty Vector");
  }
  return it_end_ + 1;
}

// Vector Capacity
template <typename T>
bool Vector<T>::empty() const {
  return it_begin_ == nullptr;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return kMaxSize;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  resize(size_);  // TODO: maybe cap should be = size
}

template <typename T>
void Vector<T>::reserve(const size_type size) {
  if (size <= capacity_) {
    return;
  }

  resize(size);
}

// Vector Modifiers
template <typename T>
void Vector<T>::clear() {
  delete[] it_begin_;
  it_begin_ = it_end_ = nullptr;
  size_ = capacity_ = 0;
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) {
  Vector temp = std::move(other);
  other = std::move(*this);
  *this = std::move(temp);
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  resize(size_ + 1);
  *it_end_ = value;
}

template <typename T>
void Vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Pop back of empty vector");
  }
  resize(size_ - 1);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  shift_left(pos, 1);
  at(pos) = value;
  return pos;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  shift_right(pos, 1);
}

}  // namespace s21
