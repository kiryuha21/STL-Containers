// Copyright 2023 School-21

#include "../include/ForwardList.h"

namespace s21 {

template <class T>
ForwardList<T>::ForwardList(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    this->push_back(i);  // size calculated here
  }
}

template <class T>
ForwardList<T>::ForwardList(const ForwardList<T> &q) {
  *this = q;
}

template <class T>
ForwardList<T>::ForwardList(ForwardList<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
ForwardList<T>::~ForwardList() noexcept {
  this->clear();
}

template <class T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T> &q) {
  if (this == &q) {
    return *this;
  }

  size_ = q.size_;
  for (INode<T> *temp = q.head_; temp != nullptr; temp = temp->get_next()) {
    push(temp->value());
  }

  return *this;
}

template <class T>
ForwardList<T> &ForwardList<T>::operator=(ForwardList<T> &&q) noexcept {
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
bool ForwardList<T>::empty() const noexcept {
  return head_ == nullptr;
}

template <class T>
typename ForwardList<T>::size_type ForwardList<T>::size() const noexcept {
  return size_;
}

template <class T>
void ForwardList<T>::swap(ForwardList &other) {
  std::swap(*this, other);
}

template <class T>
typename ForwardList<T>::const_reference ForwardList<T>::front() const {
  if (head_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }
  return head_->value();
}

template <class T>
typename ForwardList<T>::const_reference ForwardList<T>::back() const {
  if (tail_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }
  return tail_->value();
}

template <class T>
void ForwardList<T>::push_back(const_reference value) {
  INode<T> *new_node = allocate_node(value);
  ++size_;

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->set_next(new_node);
    tail_ = new_node;
  }
}

template <class T>
void ForwardList<T>::push_front(const_reference value) {
  INode<T> *new_node = allocate_node(value);
  ++size_;

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->set_next(head_);
    head_ = new_node;
  }
}

template <class T>
void ForwardList<T>::pop_back() {
  if (tail_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }

  --size_;
  INode<T> *temp = head_;
  for (; temp->get_next() != tail_; temp = temp->get_next()) {
  }
  tail_ = temp;
  delete tail_->get_next();
}

template <class T>
void ForwardList<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }

  --size_;
  INode<T> *temp = head_;
  head_ = head_->get_next();
  delete temp;
}

template <class T>
INode<T> *ForwardList<T>::allocate_node(value_type value) const {
  INode<T> *new_node = nullptr;

  try {
    new_node = new UNode<T>(value);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  return new_node;
}

template <class T>
void ForwardList<T>::clear() noexcept {
  for (INode<T> *temp = head_; temp != nullptr; temp = head_) {
    head_ = head_->get_next();
    delete temp;
  }
}

}  // namespace s21
