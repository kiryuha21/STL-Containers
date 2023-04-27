// Copyright 2023 school-21

#ifndef SRC_SOURCE_BSTREE_H_
#define SRC_SOURCE_BSTREE_H_

#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "tree_node.h"

namespace s21 {
template <class V, class K, class T>  // V must be class(contain node_ and
                                      // key_type key()), K - key_type
class bs_tree {
 public:
  using value_type = V;
  using key_type = K;
  using obj_type = T;
  using reference = V &;
  using const_reference = const V &;
  using iterator = typename tree_node<V, K, T>::TreeIterator;
  using const_iterator = typename tree_node<V, K, T>::TreeConstIterator;
  using size_type = size_t;

  bs_tree() noexcept = default;
  bs_tree(std::initializer_list<value_type> const &items);
  bs_tree(const bs_tree &other);
  bs_tree(bs_tree &&other) noexcept;
  explicit bs_tree(const value_type &value) noexcept;

  ~bs_tree() noexcept;

  bs_tree &operator=(const bs_tree &other);
  bs_tree &operator=(bs_tree &&other) noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;
  [[nodiscard]] size_type max_size() const noexcept;

  void clear() noexcept;
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(bs_tree &other) noexcept;
  void merge(bs_tree &other);

  iterator find(const key_type &key) const noexcept;
  [[nodiscard]] bool contains(const key_type &key) const noexcept;

 private:
  tree_node<value_type, key_type, obj_type> *root_ = nullptr;
};

template <class V, class K, class T>
bs_tree<V, K, T>::bs_tree(std::initializer_list<value_type> const &items) {
  for (const auto &elem : items) {
    insert(elem);
  }
}

template <class V, class K, class T>
bs_tree<V, K, T>::bs_tree(const bs_tree &other) {
  *this = other;
}

template <class V, class K, class T>
bs_tree<V, K, T>::bs_tree(bs_tree &&other) noexcept {
  *this = std::move(other);
}

template <class V, class K, class T>
bs_tree<V, K, T>::bs_tree(const value_type &value) noexcept {
  insert(value);
}

template <class V, class K, class T>
bs_tree<V, K, T>::~bs_tree() noexcept {
  clear();
}

template <class V, class K, class T>
bs_tree<V, K, T> &bs_tree<V, K, T>::operator=(const bs_tree &other) {
  if (this == &other) {
    return *this;
  }

  clear();

  for (iterator b = other.begin(); b != other.end(); ++b) {
    insert(*b);
  }

  return *this;
}

template <class V, class K, class T>
bs_tree<V, K, T> &bs_tree<V, K, T>::operator=(bs_tree &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  clear();

  root_ = std::exchange(other.root_, nullptr);

  return *this;
}

template <class V, class K, class T>
typename bs_tree<V, K, T>::iterator bs_tree<V, K, T>::begin() const noexcept {
  if (!root_) {
    return iterator(nullptr, true);
  }

  return iterator(root_->front(), false);
}

template <class V, class K, class T>
typename bs_tree<V, K, T>::iterator bs_tree<V, K, T>::end() const noexcept {
  if (!root_) {
    return iterator(nullptr, true);
  }

  return iterator(root_->back(), true);
}

template <class V, class K, class T>
[[nodiscard]] bool bs_tree<V, K, T>::empty() const noexcept {
  return root_ == nullptr;
}

template <class V, class K, class T>
[[nodiscard]] typename bs_tree<V, K, T>::size_type bs_tree<V, K, T>::size()
    const noexcept {
  if (!root_) {
    return 0;
  }
  return root_->size();
}

template <class V, class K, class T>
[[nodiscard]] typename bs_tree<V, K, T>::size_type bs_tree<V, K, T>::max_size()
    const noexcept {
  return size_type(-1) / sizeof(tree_node<V, K, T>);
}

template <class V, class K, class T>
void bs_tree<V, K, T>::clear() noexcept {
  delete root_;
  root_ = nullptr;
}

template <class V, class K, class T>
typename bs_tree<V, K, T>::iterator bs_tree<V, K, T>::insert(
    const typename bs_tree<V, K, T>::value_type &value) {
  if (!root_) {
    root_ = new tree_node<value_type, key_type, obj_type>(value);
    return iterator(root_);
  }

  return root_->insert(value);
}

template <class V, class K, class T>
void bs_tree<V, K, T>::erase(iterator pos) {
  if (!root_) {
    throw std::out_of_range("Already empty");
  } else if (pos == end()) {
    throw std::out_of_range("End erase");
  } else if (pos.get_node() == root_ && !root_->get_right() &&
             !root_->get_left()) {
    delete root_;
    root_ = nullptr;
  } else {
    root_->erase(pos);
  }
}

template <class V, class K, class T>
void bs_tree<V, K, T>::swap(bs_tree &other) noexcept {
  std::swap(root_, other.root_);
}

template <class V, class K, class T>
void bs_tree<V, K, T>::merge(bs_tree &other) {
  for (iterator elem = other.begin(); elem != other.end(); ++elem) {
    insert(*elem);
  }
}

template <class V, class K, class T>
typename bs_tree<V, K, T>::iterator bs_tree<V, K, T>::find(
    const key_type &key) const noexcept {
  if (!root_) {
    return end();
  }
  typename tree_node<value_type, key_type, obj_type>::iterator it =
      root_->find(key);
  if (it == nullptr) {
    return end();
  }
  return iterator(it);
}

template <class V, class K, class T>
[[nodiscard]] bool bs_tree<V, K, T>::contains(
    const key_type &key) const noexcept {
  return find(key) != end();
}

}  // namespace s21
#endif  // SRC_SOURCE_BSTREE_H_
