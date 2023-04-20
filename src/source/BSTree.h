// Copyright 2023 school-21

#ifndef SRC_SOURCE_BSTREE_H_
#define SRC_SOURCE_BSTREE_H_

#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "TreeNode.h"

namespace bstree {
template <class V, class K, class T>  // V must be class(contain node_ and
                                      // key_type key()), K - key_type
class BSTree {
 public:
  using value_type = V;
  using key_type = K;
  using obj_type = T;
  using reference = V &;
  using const_reference = const V &;
  using iterator = typename tree_node::TreeNode<V, K, T>::TreeIterator;
  using const_iterator =
      typename tree_node::TreeNode<V, K, T>::TreeConstIterator;
  using size_type = size_t;

  BSTree() noexcept = default;
  BSTree(std::initializer_list<value_type> const &items);
  BSTree(const BSTree &other);
  BSTree(BSTree &&other) noexcept;
  explicit BSTree(const value_type &value) noexcept;

  ~BSTree() noexcept;

  BSTree &operator=(const BSTree &other);
  BSTree &operator=(BSTree &&other) noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;
  [[nodiscard]] size_type max_size() const noexcept;

  void clear() noexcept;
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(BSTree &other) noexcept;
  void merge(BSTree &other);

  iterator find(const key_type &key) const noexcept;
  [[nodiscard]] bool contains(const key_type &key) const noexcept;

 private:
  tree_node::TreeNode<value_type, key_type, obj_type> *root_ = nullptr;
};

template <class V, class K, class T>
BSTree<V, K, T>::BSTree(std::initializer_list<value_type> const &items) {
  for (const auto &elem : items) {
    insert(elem);
  }
}

template <class V, class K, class T>
BSTree<V, K, T>::BSTree(const BSTree &other) {
  *this = other;
}

template <class V, class K, class T>
BSTree<V, K, T>::BSTree(BSTree &&other) noexcept {
  *this = std::move(other);
}

template <class V, class K, class T>
BSTree<V, K, T>::BSTree(const value_type &value) noexcept {
  insert(value);
}

template <class V, class K, class T>
BSTree<V, K, T>::~BSTree() noexcept {
  clear();
}

template <class V, class K, class T>
BSTree<V, K, T> &BSTree<V, K, T>::operator=(const BSTree &other) {
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
BSTree<V, K, T> &BSTree<V, K, T>::operator=(BSTree &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  clear();

  root_ = std::exchange(other.root_, nullptr);

  return *this;
}

template <class V, class K, class T>
typename BSTree<V, K, T>::iterator BSTree<V, K, T>::begin() const noexcept {
  if (!root_) {
    return iterator(nullptr, true);
  }

  return iterator(root_->front(), false);
}

template <class V, class K, class T>
typename BSTree<V, K, T>::iterator BSTree<V, K, T>::end() const noexcept {
  if (!root_) {
    return iterator(nullptr, true);
  }

  return iterator(root_->back(), true);
}

template <class V, class K, class T>
[[nodiscard]] bool BSTree<V, K, T>::empty() const noexcept {
  return root_ == nullptr;
}

template <class V, class K, class T>
[[nodiscard]] typename BSTree<V, K, T>::size_type BSTree<V, K, T>::size()
    const noexcept {
  if (!root_) {
    return 0;
  }
  return root_->size();
}

template <class V, class K, class T>
[[nodiscard]] typename BSTree<V, K, T>::size_type BSTree<V, K, T>::max_size()
    const noexcept {
  return size_type(-1) / sizeof(tree_node::TreeNode<V, K, T>);
}

template <class V, class K, class T>
void BSTree<V, K, T>::clear() noexcept {
  delete root_;
  root_ = nullptr;
}

template <class V, class K, class T>
typename BSTree<V, K, T>::iterator BSTree<V, K, T>::insert(
    const typename BSTree<V, K, T>::value_type &value) {
  if (!root_) {
    root_ = new tree_node::TreeNode<value_type, key_type, obj_type>(value);
    return iterator(root_);
  }

  return root_->insert(value);
}

template <class V, class K, class T>
void BSTree<V, K, T>::erase(iterator pos) {
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
void BSTree<V, K, T>::swap(BSTree &other) noexcept {
  std::swap(root_, other.root_);
}

template <class V, class K, class T>
void BSTree<V, K, T>::merge(BSTree &other) {
  for (iterator elem = other.begin(); elem != other.end(); ++elem) {
    insert(*elem);
  }
}

template <class V, class K, class T>
typename BSTree<V, K, T>::iterator BSTree<V, K, T>::find(
    const key_type &key) const noexcept {
  if (!root_) {
    return end();
  }
  typename tree_node::TreeNode<value_type, key_type, obj_type>::iterator it =
      root_->find(key);
  if (it == nullptr) {
    return end();
  }
  return iterator(it);
}

template <class V, class K, class T>
[[nodiscard]] bool BSTree<V, K, T>::contains(
    const key_type &key) const noexcept {
  return find(key) != end();
}

}  // namespace bstree
#endif  // SRC_SOURCE_BSTREE_H_