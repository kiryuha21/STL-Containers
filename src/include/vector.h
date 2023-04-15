// Copyright 2023 School-21

#ifndef SRC_INCLUDE_VECTOR_H_
#define SRC_INCLUDE_VECTOR_H_

#include <cstdlib>
#include <initializer_list>

namespace s21 {
// TODO: add noexcept
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector operator=(const vector &v);
  vector operator=(vector &&v);

  reference at(size_type pos) const;
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;

  iterator data() const;
  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type type);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  iterator it_begin_ = nullptr;
  iterator it_end_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;
};
}  // namespace s21

#endif  // SRC_INCLUDE_VECTOR_H_
