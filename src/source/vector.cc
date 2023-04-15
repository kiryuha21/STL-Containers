#include "../include/vector.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class T>
void vector<T>::allocate_memory(const size_type n) {
  if (n <= 0) {
    throw std::out_of_range("Vector size must be >= 0");
  }

  capacity_ = 2 * (size_type(std::log(n) / std::log(2)));

  try {
    it_begin_ = new T[capacity_];
  } catch (const std::bad_alloc& exp) {
    capacity_ = 0;
    throw std::out_of_range("Alloc error");
  }

  size_ = n;
  it_end_ = it_begin_ + n + 1;
}

template <class T>
vector<T>::vector() noexcept {}

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
vector<T> vector<T>::operator=(const vector<T>& v) noexcept {
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
vector<T> vector<T>::operator=(vector<T>&& v) noexcept {
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
  delete[] it_begin_;
  it_begin_ = nullptr;
  it_end_ = nullptr;
  capacity_ = 0;
  size_ = 0;
}

}  // namespace s21