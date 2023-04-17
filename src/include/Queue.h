// Copyright 2023 School-21

#ifndef SRC_INCLUDE_QUEUE_H_
#define SRC_INCLUDE_QUEUE_H_

#include "ForwardList.h"

namespace s21 {

template <class T>
class Queue : public ForwardList<T> {
 public:
  using value_type = typename ForwardList<T>::value_type;
  using reference = typename ForwardList<T>::reference;
  using const_reference = typename ForwardList<T>::const_reference;
  using size_type = typename ForwardList<T>::size_type;

  Queue() = default;
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue() noexcept override;
  Queue &operator=(const Queue &q);
  Queue &operator=(Queue &&q) noexcept;

  using ForwardList<T>::front;
  using ForwardList<T>::back;

  void push(const_reference value);
  void pop();
};

}  // namespace s21

#endif  // SRC_INCLUDE_QUEUE_H_
