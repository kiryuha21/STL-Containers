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

  if (capacity_ < n) {
    capacity_ = calculate_capacity(n);
  }

  if (n != 0) {
    try {
      delete[] it_begin_;
      it_begin_ = new value_type[capacity_];
    } catch (const std::bad_alloc& exc) {
      capacity_ = 0;
      throw std::out_of_range("Alloc error in allocate_memory");
    }

    it_end_ = it_begin_ + n - 1;
    std::fill(begin(), end(), value_type());
  }

  size_ = n;
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

  allocate_memory(n);
}

template <class T>
typename Vector<T>::size_type Vector<T>::calculate_capacity(
    const size_type size) const noexcept {
  if (size == 0) {
    return 1;
  }

  auto res = static_cast<size_type>(pow(
      size, static_cast<double>(std::ceil(std::log(size) / std::log(size)))));

  return res;
}

template <class T>
void Vector<T>::shift_right(const size_type shift_after,
                            const size_type shift_on) {
  Vector<value_type> buff(*this);
  resize(size_ + shift_on);
  if (!buff.empty()) {
    std::copy(buff.begin() + shift_after, buff.end(),
              begin() + shift_after + shift_on);
  }
}

template <class T>
void Vector<T>::shift_left(const size_type shift_after,
                           const size_type shift_on) {
  if (size_ < shift_on + shift_after) {
    throw std::out_of_range("Shift left on too big value");
  }

  Vector<value_type> buff(*this);
  resize(size_ - shift_on);
  std::copy(buff.begin() + shift_after + shift_on, buff.end(),
            begin() + shift_after);
}

// Vector Member type
template <class T>
Vector<T>::Vector(const size_type n) {
  allocate_memory(n);
}

template <class T>
Vector<T>::Vector(std::initializer_list<value_type> const& items) {
  allocate_memory(items.size());
  std::copy(items.begin(), items.end(), it_begin_);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
  if (this == &v) {
    return *this;
  }

  allocate_memory(v.capacity_);
  size_ = v.size_;
  it_end_ = it_begin_ + size_ - 1;
  if (!v.empty()) {
    std::copy(v.begin(), v.end(), begin());
  }

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

  delete[] it_begin_;

  it_begin_ = std::exchange(v.it_begin_, nullptr);
  it_end_ = std::exchange(v.it_end_, nullptr);
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
  delete[] it_begin_;
}

// Vector Element access
template <class T>
typename Vector<T>::reference Vector<T>::at(const size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Wrong position for at");
  } else if (empty()) {
    throw std::out_of_range("Taking at of empty Vector");
  }

  return it_begin_[pos];
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
  return at(0);
}

template <class T>
typename Vector<T>::const_reference Vector<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Taking back of empty Vector");
  }
  return *it_end_;
}

template <class T>
typename Vector<T>::iterator Vector<T>::data() const {
  return it_begin_;
}

// Vector Iterators
template <class T>
typename Vector<T>::iterator Vector<T>::begin() const noexcept {
  return it_begin_;
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() const noexcept {
  return it_end_ + 1;
}

// Vector Capacity
template <class T>
bool Vector<T>::empty() const noexcept {
  return it_begin_ == nullptr;
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
  return kMaxSize;
}

template <class T>
void Vector<T>::shrink_to_fit() {
  resize(size_);  // TODO(guinicyb): maybe cap should be = size
}

template <class T>
void Vector<T>::reserve(const size_type size) {
  if (size <= capacity_) {
    return;
  }

  resize(size);
}

// Vector Modifiers
template <class T>
void Vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
void Vector<T>::swap(Vector<T>& other) noexcept {
  Vector temp = std::move(other);
  other = std::move(*this);
  *this = std::move(temp);
}

template <class T>
void Vector<T>::push_back(const_reference value) {
  resize(size_ + 1);
  *it_end_ = value;
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
  auto res_position = size_type(pos - it_begin_);
  shift_right(res_position, 1);
  *(it_begin_ + res_position) = value;
  return it_begin_ + res_position;
}

template <class T>
void Vector<T>::erase(iterator pos) {
  if (empty()) {
    throw std::out_of_range("Erase of empty vector");
  }
  auto res_position = size_type(pos - it_begin_);
  shift_left(res_position, 1);
}

}  // namespace s21
