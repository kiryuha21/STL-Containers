// Copyright 2023 School-21

#ifndef SRC_INCLUDE_VECTOR_H_
#define SRC_INCLUDE_VECTOR_H_

#include <cstdlib>
#include <initializer_list>

namespace s21 {

// TODO: add noexcept
template <class T>
class Vector {
 public:
  // Vector Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Vector Member functions
  Vector() noexcept = default;
  Vector(const size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v) noexcept;
  Vector(Vector &&v) noexcept;
  ~Vector() noexcept;
  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v) noexcept;

  // Vector Element access
  reference at(const size_type pos) const;
  reference operator[](const size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data() const;

  // Vector Iterators
  iterator begin() const;
  iterator end() const;

  // Vector Capacity
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  [[nodiscard]] size_type max_size() const;
  void reserve(const size_type size);
  [[nodiscard]] size_type capacity() const;
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

 private:
  // Vector Attributes
  iterator it_begin_ = nullptr;
  iterator it_end_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  // Helpers
  void allocate_memory(const size_type n);
  void resize(const size_type n);
  [[nodiscard]] size_type calculate_capacity(
      const size_type size) const noexcept;
  void shift_left(iterator shift_from, const size_type shift_on);
  void shift_right(iterator shift_from, const size_type shift_on);
};

}  // namespace s21

#endif  // SRC_INCLUDE_VECTOR_H_
