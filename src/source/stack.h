// Copyright 2023 School-21

#ifndef SRC_SOURCE_STACK_H_
#define SRC_SOURCE_STACK_H_

#include <utility>

#include "forward_list.h"

namespace s21 {

template <class T>
class stack : public forward_list<T> {
 public:
  using value_type = typename forward_list<T>::value_type;
  using reference = typename forward_list<T>::reference;
  using const_reference = typename forward_list<T>::const_reference;
  using size_type = typename forward_list<T>::size_type;

  stack() = default;
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &q);
  stack(stack &&q) noexcept;
  ~stack() noexcept override;
  stack &operator=(const stack &q);
  stack &operator=(stack &&q) noexcept;

  const_reference top() const;

  // inherited empty() and size()

  void push(const_reference value);
  void pop();
  // inherited swap()
};

template <class T>
stack<T>::stack(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    push(i);
  }
}

template <class T>
stack<T>::stack(const stack<T> &q) : forward_list<T>() {
  *this = q;
}

template <class T>
stack<T>::stack(stack<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
stack<T>::~stack() noexcept {
  this->clear();
}

template <class T>
stack<T> &stack<T>::operator=(const stack<T> &q) {
  if (this == &q) {
    return *this;
  }

  this->clear();
  for (list_node<T> *temp = q.head_; temp != nullptr; temp = temp->get_next()) {
    this->push_back(temp->value());
  }

  return *this;
}

template <class T>
stack<T> &stack<T>::operator=(stack<T> &&q) noexcept {
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
typename stack<T>::const_reference stack<T>::top() const {
  return this->front();
}

template <class T>
void stack<T>::push(const_reference value) {
  this->push_front(value);
}

template <class T>
void stack<T>::pop() {
  this->pop_front();
}

}  // namespace s21

#endif  // SRC_SOURCE_STACK_H_
