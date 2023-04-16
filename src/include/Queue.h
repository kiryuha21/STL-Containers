// Copyright 2023 School-21

#ifndef SRC_INCLUDE_QUEUE_H_
#define SRC_INCLUDE_QUEUE_H_

#include "List.h"

namespace s21 {

template <class T>
class Queue : public List<T> {
 public:
  using value_type = typename Container<T>::value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using size_type = typename Container<T>::size_type;

  Queue() = default;
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue() noexcept override;
  Queue &operator=(const Queue &q);
  Queue &operator=(Queue &&q) noexcept;

  void push(const_reference value);
  void pop();
  void swap(Queue &other);

 private:
  using Node = typename List<T>::Node;
};
}  // namespace s21

#endif  // SRC_INCLUDE_QUEUE_H_
