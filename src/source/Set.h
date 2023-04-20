// Copyright 2023 school-21

#ifndef SRC_SOURCE_SET_H_
#define SRC_SOURCE_SET_H_

#include "BSTree.h"

namespace s21 {

template <class V>
class Set : public Container<V> {
 private:
  struct KeyTreeNode;

 public:
  using value_type = V;
  using key_type = V;
  using iterator =
      typename bstree::BSTree<KeyTreeNode, key_type, value_type>::iterator;
  using const_iterator = typename bstree::BSTree<KeyTreeNode, key_type,
                                                 value_type>::const_iterator;
  using reference = V &;
  using const_reference = const V &;
  using size_type = size_t;

  Set() noexcept = default;
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &other) noexcept;
  Set(Set &&other) noexcept;
  Set &operator=(const Set &s) noexcept;
  Set &operator=(Set &&s) noexcept;

  ~Set() noexcept = default;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  [[nodiscard]] bool empty() const noexcept override;
  [[nodiscard]] size_type size() const noexcept override;
  [[nodiscard]] size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(Set &other) noexcept;
  void merge(Set &other);

  iterator find(const key_type &key) const noexcept;
  [[nodiscard]] bool contains(const key_type &key) const noexcept;

 private:
  struct KeyTreeNode {
   public:
    using value_type = V;
    [[nodiscard]] value_type key() const noexcept;
    KeyTreeNode() noexcept = default;
    KeyTreeNode(value_type value) noexcept;
    value_type value_ = value_type();
  };

  bstree::BSTree<KeyTreeNode, key_type, value_type> tree_ =
      bstree::BSTree<KeyTreeNode, key_type, value_type>();
};

template <class V>
Set<V>::Set(const Set &other) noexcept {
  *this = other;
}

template <class V>
Set<V>::Set(Set &&other) noexcept {
  *this = std::move(other);
}

template <class V>
Set<V> &Set<V>::operator=(const Set &s) noexcept {
  tree_ = s.tree_;
  return *this;
}

template <class V>
Set<V> &Set<V>::operator=(Set &&s) noexcept {
  tree_ = std::move(s.tree_);
  return *this;
}

template <class V>
typename Set<V>::iterator Set<V>::begin() const noexcept {
  return tree_.begin();
}

template <class V>
typename Set<V>::iterator Set<V>::end() const noexcept {
  return tree_.end();
}

template <class V>
bool Set<V>::empty() const noexcept {
  return size() == 0;
}

template <class V>
typename Set<V>::size_type Set<V>::size() const noexcept {
  return tree_.size();
}

template <class V>
typename Set<V>::size_type Set<V>::max_size() const noexcept {
  return tree_.max_size();
}

template <class V>
void Set<V>::clear() noexcept {
  tree_.clear();
}

template <class V>
void Set<V>::erase(Set::iterator pos) {
  tree_.erase(pos);
}

template <class V>
void Set<V>::swap(Set &other) noexcept {
  tree_.swap(other.tree_);
}

template <class V>
void Set<V>::merge(Set &other) {
  Set<V> res;
  for (auto elem = other.begin(); elem != other.end(); ++elem) {
    if (!contains(*elem)) {
      insert(*elem);
    } else {
      res.insert(*elem);
    }
  }
  other = res;
}

template <class V>
bool Set<V>::contains(const key_type &key) const noexcept {
  return tree_.contains(key);
}

template <class V>
typename Set<V>::iterator Set<V>::find(const key_type &key) const noexcept {
  return tree_.find(key);
}

template <class V>
[[nodiscard]] typename Set<V>::value_type Set<V>::KeyTreeNode::key()
    const noexcept {
  return value_;
}

template <class V>
Set<V>::KeyTreeNode::KeyTreeNode(value_type value) noexcept : value_(value) {}

template <class V>
std::pair<typename Set<V>::iterator, bool> Set<V>::insert(
    const value_type &value) {
  if (!contains(value)) {
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::pair<iterator, bool>(tree_.end(), false);
}

template <class V>
Set<V>::Set(std::initializer_list<value_type> const &items) {
  for (auto elem : items) {
    insert(elem);
  }
}

}  // namespace s21
#endif  // SRC_SOURCE_SET_H_
