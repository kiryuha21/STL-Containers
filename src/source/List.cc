// Copyright 2023 School-21

#include "../include/List.h"

namespace s21 {

template <class T>
List<T>::List(List::size_type n) {
  this->size_ = n;
  this->head_ = allocate_node({});
  this->tail_ = this->head_;
  for (int i = 0; i < n - 1; ++i) {
    this->tail_->set_next(allocate_node({}));
    this->tail_->get_next()->set_prev(this->tail_);
    this->tail_ = this->tail_->get_next();
  }
}

template <class T>
List<T>::List(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    this->push_back(i);
  }
}

template <class T>
List<T>::List(const List &l) : List<T>() {
  *this = l;
}

template <class T>
List<T>::List(List &&l) noexcept {
  *this = std::move(l);
}

template <class T>
List<T>::~List() noexcept {
  this->clear();
}

template <class T>
List<T> &List<T>::operator=(const List &l) {
  if (this == &l) {
    return *this;
  }

  this->clear();
  for (INode<T> *temp = l.head_; temp != nullptr; temp = temp->next) {
    push_back(temp->value);
  }

  return *this;
}

template <class T>
List<T> &List<T>::operator=(List &&l) noexcept {
  if (this == &l) {
    return *this;
  }

  this->clear();

  this->head_ = std::exchange(l.head_, nullptr);
  this->tail_ = std::exchange(l.tail_, nullptr);
  this->size_ = std::exchange(l.size_, 0);

  return *this;
}

template <class T>
typename List<T>::iterator List<T>::begin() const {
  return ListIterator(this->head_);
}

template <class T>
typename List<T>::iterator List<T>::end() const {
  return ListIterator(this->tail_);
}

// FIXME(lyradanu): 100% incorrect
template <class T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return std::numeric_limits<BiNode<T>>::max();
}

template <class T>
void List<T>::push_back(const_reference val) {
  INode<T> *temp = this->tail_;
  ForwardList<T>::push_back(val);
  if (this->head_ != this->tail_) {
    this->tail_->set_prev(temp);
  }
}

template <class T>
void List<T>::pop_back() {
  if (this->tail_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }

  --this->size_;
  this->tail_ = this->tail_->get_prev();
  delete this->tail_->get_next();
}

template <class T>
void List<T>::push_front(const_reference val) {
  INode<T> *temp = this->head_;
  ForwardList<T>::push_front(val);
  if (this->head_ != this->tail_) {
    temp->set_prev(this->head_);
  }
}

template <class T>
void List<T>::pop_front() {
  ForwardList<T>::pop_front();
  this->head_->set_prev(nullptr);
}

template <class T>
typename List<T>::iterator &List<T>::ListIterator::operator--() {
  return node_->get_prev();
}

template <class T>
typename List<T>::iterator &List<T>::ListIterator::operator++() {
  return node_->get_next();
}

template <class T>
bool List<T>::ListIterator::operator==(const iterator &other) {
  return node_ == other.node_;
}

template <class T>
bool List<T>::ListIterator::operator!=(const iterator &other) {
  return node_ != other.node_;
}

template <class T>
typename List<T>::reference List<T>::ListIterator::operator*() {
  return node_->get_value();
}

template <class T>
typename List<T>::const_iterator &List<T>::ListConstIterator::operator--() {
  return node_->get_prev();
}

template <class T>
typename List<T>::const_iterator &List<T>::ListConstIterator::operator++() {
  return node_->get_next();
}

template <class T>
bool List<T>::ListConstIterator::operator==(List::const_iterator &other) {
  return node_ == other.node_;
}

template <class T>
bool List<T>::ListConstIterator::operator!=(List::const_iterator &other) {
  return node_ != other.node_;
}

template <class T>
typename List<T>::const_reference List<T>::ListConstIterator::operator*() {
  return node_->get_value();
}

template <class T>
INode<T> *List<T>::allocate_node(value_type value) const {
  INode<T> *new_node = nullptr;

  try {
    new_node = new BiNode<T>(value);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  return new_node;
}

}  // namespace s21
