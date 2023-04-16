#include "../include/Queue.h"

namespace s21 {
template <class T>
Queue<T>::Queue(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    push(i);
  }
}

template <class T>
Queue<T>::Queue(const Queue<T> &q) {
  *this = q;
}

template <class T>
Queue<T>::Queue(Queue<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
Queue<T>::~Queue() {
  clear();
}

template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &q) {
  if (this == &q) {
    return *this;
  }

  std::copy(q.head_, q.tail_, head_);
}

template <class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&q) noexcept {
  if (this == &q) {
    return *this;
  }

  clear();

  head_ = std::exchange(q.head_, nullptr);
  tail_ = std::exchange(q.tail_, nullptr);

  return *this;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (head_ == nullptr) {
    throw std::out_of_range(kEmptyQueueMsg);
  }
  return head_->value;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (tail_ == nullptr) {
    throw std::out_of_range(kEmptyQueueMsg);
  }
  return tail_->value;
}

template <class T>
bool Queue<T>::empty() const noexcept {
  return head_ == nullptr;
}

template <class T>
typename Queue<T>::size_type Queue<T>::size() const noexcept {
  size_type result = 0;
  for (Node *temp = head_; temp != nullptr; temp = temp->next, ++result) {
  }
  return result;
}

template <class T>
void Queue<T>::push(const_reference value) {
  Node *new_node = nullptr;
  try {
    new_node = new Node;
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  new_node->value = value;
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    tail_ = new_node;
  }
}

template <class T>
void Queue<T>::pop() {
  if (head_ == nullptr) {
    throw std::out_of_range(kEmptyQueueMsg);
  }

  Node *temp = head_;
  head_ = head_->next;
  delete temp;
}

template <class T>
void Queue<T>::swap(Queue &other) {
  Queue<T> temp = std::move(other);
  other = std::move(*this);
  *this = std::move(temp);
}

template <class T>
void Queue<T>::clear() {
  for (Node *temp = head_; temp != nullptr; temp = head_) {
    head_ = head_->next;
    delete temp;
  }
}
}  // namespace s21
