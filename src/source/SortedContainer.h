// Copyright 2023 school-21

#ifndef SRC_SOURCE_SORTEDCONTAINER_H_
#define SRC_SOURCE_SORTEDCONTAINER_H_

#include <initializer_list>
#include <utility>

#include "Container.h"

namespace s21 {

template <class T>
class SortedContainer : public Container<T> {
 private:
  struct Node;

 public:
  class SortedIterator;
  class SortedConstIterator;

  using value_type = typename Container<T>::value_type;
  using key_type = value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using iterator = SortedIterator;
  using const_iterator = SortedConstIterator;
  using size_type = typename Container<T>::size_type;

  SortedContainer() noexcept = default;
  SortedContainer(std::initializer_list<value_type> const &items);
  SortedContainer(const SortedContainer &s);
  SortedContainer(SortedContainer &&s) noexcept;
  ~SortedContainer();
  SortedContainer &operator=(const SortedContainer &s) noexcept;
  SortedContainer &operator=(SortedContainer &&s) noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void clear() noexcept;

  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(SortedContainer &other);

  void merge(SortedContainer &other);

  iterator find(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;

  class SortedIterator {
   public:
    explicit SortedIterator(Node *node) : node_(node) {}

    iterator operator+();
    iterator operator-();
    iterator &operator--();
    iterator &operator++();
    reference operator*();

   private:
    Node *node_ = nullptr;
  };

  class SortedConstIterator {
   public:
    explicit SortedConstIterator(Node *node) : node_(node) {}
    const_iterator operator+();
    const_iterator operator-();
    const_iterator &operator--();
    const_iterator &operator++();
    const_reference operator*();

   private:
    Node *node_ = nullptr;
  };

 private:
  struct Node {
   public:
    Node() noexcept = default;
    explicit Node(value_type value) : value_(value) {}
    virtual key_type key() const noexcept { return value_; };
    virtual value_type value() const noexcept { return value_; };
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

   private:
    value_type value_ = value_type();
  };

  Node *find_previous(const key_type &key) const noexcept;

  Node *root_ = nullptr;
  size_type size_ = 0;
};

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

#endif  // SRC_SOURCE_SORTEDCONTAINER_H_
