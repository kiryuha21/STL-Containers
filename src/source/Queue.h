// Copyright 2023 School-21

#ifndef SRC_SOURCE_QUEUE_H_
#define SRC_SOURCE_QUEUE_H_

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

  // inherited empty() and size()

  void push(const_reference value);
  void pop();
  // inherited swap()
};

template <class T>
Queue<T>::Queue(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    push(i);
  }
}

template <class T>
Queue<T>::Queue(const Queue<T> &q) : ForwardList<T>() {
  *this = q;
}

template <class T>
Queue<T>::Queue(Queue<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
Queue<T>::~Queue() noexcept {
  this->clear();
}

template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &q) {
  if (this == &q) {
    return *this;
  }

  this->clear();
  for (INode<T> *temp = q.head_; temp != nullptr; temp = temp->get_next()) {
    push(temp->value());
  }

  return *this;
}

template <class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&q) noexcept {
  if (this == &q) {
    return *this;
  }

  this->clear();

  this->head_ = std::exchange(q.head_, nullptr);
  this->tail_ = std::exchange(q.tail_, nullptr);
  this->size_ = std::exchange(q.size_, 0);

  return *this;
}

template <class T>
void Queue<T>::push(const_reference value) {
  this->push_back(value);
}

template <class T>
void Queue<T>::pop() {
  this->pop_front();
}

}  // namespace s21

#endif  // SRC_SOURCE_QUEUE_H_
