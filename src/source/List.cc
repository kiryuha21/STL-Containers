#include "../include/List.h"

namespace s21 {

template <class T>
void List<T>::allocate_nodes(List::size_type size) {
  head_ = new Node;
  tail_ = head_;
  for (int i = 0; i < size - 1; ++i) {
    tail_->next = new Node;
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  }
}

template <class T>
List<T>::List(List::size_type n) {
  try {
      allocate_nodes(n);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }
}

template <class T>
List<T>::List(const std::initializer_list<value_type> &items) {
    try {
        allocate_nodes(items.size());
    } catch (std::bad_alloc &e) {
        std::throw_with_nested(e);
    }
}

template <class T>
List<T>::List(const List &l) {
    *this = l;
}

template <class T>
List<T>::List(List &&l) noexcept {
    *this = std::move(l);
}

template <class T>
List<T>::~List() noexcept {
  clear();
}

template <class T>
List<T> &List<T>::operator=(const List &l) {
  if (this == &l) {
    return *this;
  }

  for (Node *temp = l.head_; temp != nullptr; temp = temp->next) {
    push_back(temp->value);
  }
}

template <class T>
List<T> &List<T>::operator=(List &&l) noexcept {
  if (this == &l) {
    return *this;
  }

  clear();

  head_ = std::exchange(l.head_, nullptr);
  tail_ = std::exchange(l.tail_, nullptr);

  return *this;
}

template <class T>
typename List<T>::const_reference List<T>::front() const {
  if (head_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }
  return head_->value;
}

template <class T>
typename List<T>::const_reference List<T>::back() const {
  if (tail_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }
  return tail_->value;
}

template <class T>
typename List<T>::iterator List<T>::begin() const {
  return ListIterator(head_);
}

template <class T>
typename List<T>::iterator List<T>::end() const {
  return ListIterator(tail_);
}

template <class T>
bool List<T>::empty() const noexcept {
  return head_ == nullptr;
}

template <class T>
typename List<T>::size_type List<T>::size() const noexcept {
  size_type result = 0;
  for (Node *temp = head_; temp != nullptr; temp = temp->next, ++result) {
  }
  return result;
}

template <class T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return std::numeric_limits<Node>::max();
}

template <class T>
void List<T>::clear() noexcept {
  for (Node *temp = head_; temp != nullptr; temp = head_) {
    head_ = head_->next;
    delete temp;
  }
}

template <class T>
void List<T>::push_back(const_reference value) {
  Node *new_node = nullptr;
  try {
    new_node = new Node(value);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    tail_ = new_node;
  }
}

template <class T>
void List<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::out_of_range(kEmptyCollectionMsg);
  }

  Node *temp = head_;
  head_ = head_->next;
  delete temp;
}

}  // namespace s21
