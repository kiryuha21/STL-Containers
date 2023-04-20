// Copyright 2023 school-21

#ifndef SRC_SOURCE_MAP_H_
#define SRC_SOURCE_MAP_H_

#include <utility>

#include "BSTree.h"
#include "Container.h"

namespace s21 {
template <class K, class T>
class Map : public Container<T> {
 private:
  struct KeyTreeNode;

 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<K, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename bstree::BSTree<KeyTreeNode, key_type, mapped_type>::iterator;
  using const_iterator = typename bstree::BSTree<KeyTreeNode, key_type,
                                                 mapped_type>::const_iterator;
  using size_type = size_t;

  Map() noexcept = default;
  Map(std::initializer_list<value_type> const &items);
  Map(const Map &m);
  Map(Map &&m) noexcept;

  ~Map() noexcept;

  Map &operator=(const Map &m);
  Map &operator=(Map &&m) noexcept;

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  iterator begin() const noexcept;
  iterator end() const noexcept;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(Map &other);
  void merge(Map &other);

  bool contains(const key_type &key);

 private:
  struct KeyTreeNode {
   public:
    [[nodiscard]] value_type key() const noexcept;
    KeyTreeNode() noexcept = default;
    KeyTreeNode(value_type value) noexcept;
    value_type value_ = value_type();
  };

  bstree::BSTree<KeyTreeNode, key_type, mapped_type> tree_ =
      bstree::BSTree<KeyTreeNode, key_type, mapped_type>();
};

template <class K, class T>
std::pair<typename Map<K, T>::iterator, bool> Map<K, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  if (contains(key)) {
    return std::pair<iterator, bool>(tree_.find(key), false);
  }
  return insert(key, obj);
}

template <class K, class T>
std::pair<typename Map<K, T>::iterator, bool> Map<K, T>::insert(
    const key_type &key, const mapped_type &obj) {
  if (!contains(key)) {
    value_type value(key, obj);
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::pair<iterator, bool>(tree_.end(), false);
}

template <class K, class T>
std::pair<typename Map<K, T>::iterator, bool> Map<K, T>::insert(
    const Map::value_type &value) {
  if (!contains(value.first)) {
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::pair<iterator, bool>(tree_.end(), false);
}

template <class K, class T>
typename Map<K, T>::mapped_type &Map<K, T>::operator[](const key_type &key) {
  iterator found = tree_.find(key);
  if (found == end()) {
    found = insert(mapped_type(), key);
  }
  return *found;
}

template <class K, class T>
typename Map<K, T>::mapped_type &Map<K, T>::at(const key_type &key) {
  iterator found = tree_.find(key);
  if (found == end()) {
    throw std::out_of_range(
        "Container does not have an element with the specified key");
  }
  return *found;
}

template <class K, class T>
void Map<K, T>::merge(Map &other) {
  Map<K, T> res;
  for (auto elem = other.begin(); elem != other.end(); ++elem) {
    if (!insert(*elem).second) {
      res.insert(*elem);
    }
  }
  other = res;
}

template <class K, class T>
void Map<K, T>::swap(Map &other) {
  tree_.swap(other.tree_);
}

template <class K, class T>
void Map<K, T>::erase(Map::iterator pos) {
  tree_.erase(pos);
}

template <class K, class T>
bool Map<K, T>::contains(const key_type &key) {
  return tree_.contains(key);
}

template <class K, class T>
typename Map<K, T>::size_type Map<K, T>::size() const noexcept {
  return tree_.size();
}

template <class K, class T>
bool Map<K, T>::empty() const noexcept {
  return size() == 0;
}

template <class K, class T>
typename Map<K, T>::iterator Map<K, T>::begin() const noexcept {
  return tree_.begin();
}

template <class K, class T>
typename Map<K, T>::iterator Map<K, T>::end() const noexcept {
  return tree_.end();
}

template <class K, class T>
Map<K, T> &Map<K, T>::operator=(Map &&m) noexcept {
  tree_ = std::move(m.tree_);
  return *this;
}

template <class K, class T>
Map<K, T> &Map<K, T>::operator=(const Map &m) {
  tree_ = m.tree_;
  return *this;
}

template <class K, class T>
Map<K, T>::Map(Map &&m) noexcept {
  *this = std::move(m);
}

template <class K, class T>
Map<K, T>::Map(const Map &m) {
  *this = m;
}

template <class K, class T>
Map<K, T>::Map(const std::initializer_list<value_type> &items) {
  for (auto elem : items) {
    insert(elem);
  }
}

template <class K, class T>
void Map<K, T>::clear() noexcept {
  tree_.clear();
}

template <class K, class T>
Map<K, T>::~Map() noexcept {
  clear();
}

template <class K, class T>
[[nodiscard]] typename Map<K, T>::value_type Map<K, T>::KeyTreeNode::key()
    const noexcept {
  return value_.first;
}

template <class K, class T>
Map<K, T>::KeyTreeNode::KeyTreeNode(value_type value) noexcept
    : value_(value) {}

}  // namespace s21

#endif  // SRC_SOURCE_MAP_H_
