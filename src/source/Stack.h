// Copyright 2023 School-21

#ifndef SRC_SOURCE_STACK_H_
#define SRC_SOURCE_STACK_H_

#include "ForwardList.h"

namespace s21 {

template <class T>
class Stack : public ForwardList<T> {
 public:
  using value_type = typename ForwardList<T>::value_type;
  using reference = typename ForwardList<T>::reference;
  using const_reference = typename ForwardList<T>::const_reference;
  using size_type = typename ForwardList<T>::size_type;

  Stack() = default;
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &q);
  Stack(Stack &&q) noexcept;
  ~Stack() noexcept override;
  Stack &operator=(const Stack &q);
  Stack &operator=(Stack &&q) noexcept;

  const_reference top() const;

  // inherited empty() and size()

  void push(const_reference value);
  void pop();
  // inherited swap()
};

template <class T>
Stack<T>::Stack(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    push(i);
  }
}

template <class T>
Stack<T>::Stack(const Stack<T> &q) : ForwardList<T>() {
  *this = q;
}

template <class T>
Stack<T>::Stack(Stack<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
Stack<T>::~Stack() noexcept {
  this->clear();
}

template <class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &q) {
  if (this == &q) {
    return *this;
  }

  this->clear();
  for (INode<T> *temp = q.head_; temp != nullptr; temp = temp->get_next()) {
    this->push_back(temp->value());
  }

  return *this;
}

template <class T>
Stack<T> &Stack<T>::operator=(Stack<T> &&q) noexcept {
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
typename Stack<T>::const_reference Stack<T>::top() const {
  return this->front();
}

template <class T>
void Stack<T>::push(const_reference value) {
  this->push_front(value);
}

template <class T>
void Stack<T>::pop() {
  this->pop_front();
}

}  // namespace s21

#endif  // SRC_SOURCE_STACK_H_
