// Copyright 2023 School-21

#ifndef SRC_SOURCE_QUEUE_H_
#define SRC_SOURCE_QUEUE_H_

#include <utility>

#include "forward_list.h"

namespace s21 {

template <class T>
class queue : public forward_list<T> {
 public:
  using value_type = typename forward_list<T>::value_type;
  using reference = typename forward_list<T>::reference;
  using const_reference = typename forward_list<T>::const_reference;
  using size_type = typename forward_list<T>::size_type;

  queue() = default;
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q) noexcept;
  ~queue() noexcept override;
  queue &operator=(const queue &q);
  queue &operator=(queue &&q) noexcept;

  using forward_list<T>::front;
  using forward_list<T>::back;

  // inherited empty() and size()

  void push(const_reference value);
  void pop();
  // inherited swap()
};

template <class T>
queue<T>::queue(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    push(i);
  }
}

template <class T>
queue<T>::queue(const queue<T> &q) : forward_list<T>() {
  *this = q;
}

template <class T>
queue<T>::queue(queue<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
queue<T>::~queue() noexcept {
  this->clear();
}

template <class T>
queue<T> &queue<T>::operator=(const queue<T> &q) {
  if (this == &q) {
    return *this;
  }

  this->clear();
  for (list_node<T> *temp = q.head_; temp != nullptr; temp = temp->get_next()) {
    push(temp->value());
  }

  return *this;
}

template <class T>
queue<T> &queue<T>::operator=(queue<T> &&q) noexcept {
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
void queue<T>::push(const_reference value) {
  this->push_back(value);
}

template <class T>
void queue<T>::pop() {
  this->pop_front();
}

}  // namespace s21

#endif  // SRC_SOURCE_QUEUE_H_
