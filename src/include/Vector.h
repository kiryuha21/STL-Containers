// Copyright 2023 School-21

#ifndef SRC_INCLUDE_VECTOR_H_
#define SRC_INCLUDE_VECTOR_H_

#include <initializer_list>

#include "Container.h"

namespace s21 {

template <class T>
class Vector : public Container<T> {
 public:
  // Vector Member type
  using value_type = typename Container<T>::value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = typename Container<T>::size_type;

  // Vector Member functions
  Vector() noexcept = default;
  Vector(const size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;
  ~Vector() noexcept override;
  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v) noexcept;

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
  [[nodiscard]] bool empty() const noexcept;
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
  void swap(Vector &other) noexcept;

 private:
  // Vector Attributes
  value_type *memory_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  static constexpr size_type kMaxSize = (size_type(1) << 61) - 1;

  // Helpers
  void allocate_memory(const size_type n);
  void resize(const size_type n);
  void recap(const size_type n);
  [[nodiscard]] size_type calculate_capacity(
      const size_type size) const noexcept;
  void shift_left(const size_type shift_after, const size_type shift_on);
  void shift_right(const size_type shift_after, const size_type shift_on);
};

}  // namespace s21

#endif  // SRC_INCLUDE_VECTOR_H_
