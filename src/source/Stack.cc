// Copyright 2023 School-21

#include "../include/Stack.h"

namespace s21 {

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
    this->push_back(temp->get_value());
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
