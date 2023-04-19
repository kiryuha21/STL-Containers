// Copyright 2023 School-21

#include "../include/SortedContainer.hpp"

namespace s21 {

template <class T>
SortedContainer<T>::SortedContainer(
    std::initializer_list<value_type> const &items) {
  for (int i = 0; i < items.size(); ++i) {
    insert(items[i]);
  }
}

template <class T>
SortedContainer<T>::SortedContainer(const SortedContainer &s) {
  *this = s;
}

template <class T>
SortedContainer<T>::SortedContainer(SortedContainer &&s) noexcept {
  *this = std::move(s);
}

template <class T>
SortedContainer<T>::~SortedContainer() {
  clear();
}

template <class T>
SortedContainer<T> &SortedContainer<T>::operator=(
    const SortedContainer<T> &s) noexcept {
  if (this == &s) {
    return *this;
  }
}  // TODO

template <class T>
SortedContainer<T> &SortedContainer<T>::operator=(
    SortedContainer<T> &&s) noexcept {
  if (this == &s) {
    return *this;
  }

  clear();
  size_ = std::exchange(s.size_, 0);
  root_ = std::exchange(s.root_, nullptr);

  return *this;
}

template <class T>
typename SortedContainer<T>::iterator
SortedContainer<T>::begin()  // TODO: CHECK
    const noexcept {
  Node *pointer = root_;
  if (pointer != nullptr) {
    while (pointer->left_ != nullptr) {
      pointer = pointer->left;
    }
  }
  return pointer;
}

template <class T>
typename SortedContainer<T>::iterator SortedContainer<T>::end()
    const noexcept {  // TODO: CHECK
  Node *pointer = root_;
  if (pointer != nullptr) {
    while (pointer->right != nullptr) {
      pointer = pointer->right;
    }
  }
  return pointer;
}

template <class T>
typename SortedContainer<T>::Node *SortedContainer<T>::find_previous(
    const key_type &key) const noexcept {
  Node *pointer = root_;

  if (pointer != nullptr) {
    bool moved;
    do {
      moved = false;
      while (pointer->left != nullptr && pointer->key() > key) {
        pointer = pointer->left;
        moved = true;
      }
      while (pointer->right != nullptr && pointer->key() < key) {
        pointer = pointer->right;
        moved = true;
      }
    } while (moved);
  }

  return pointer;
}

template <class T>
typename SortedContainer<T>::iterator SortedContainer<T>::find(
    const key_type &key) const noexcept {
  Node *result = find_previous(key);

  if (result != nullptr) {
    if (result->left->key() == key) {
      result = result->left;
    } else if (result->right->key() == key) {
      result = result->right;
    } else {
      result = end();
    }
  } else {
    result = end();
  }

  return result;
}

template <class T>
bool SortedContainer<T>::contains(const key_type &key) const noexcept {
  if (end() == nullptr) {
    return false;
  }

  return find(key)->key() == key;
}

template <class T>
bool SortedContainer<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
typename SortedContainer<T>::size_type SortedContainer<T>::size()
    const noexcept {
  return size_;
}

template <class T>
typename SortedContainer<T>::size_type SortedContainer<T>::max_size()
    const noexcept {}  // TODO

}  // namespace s21
