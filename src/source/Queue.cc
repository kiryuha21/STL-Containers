// Copyright 2023 School-21

#include "../include/Queue.h"

namespace s21 {

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
