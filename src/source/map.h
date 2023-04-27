// Copyright 2023 school-21

#ifndef SRC_SOURCE_MAP_H_
#define SRC_SOURCE_MAP_H_

#include <utility>

#include "bs_tree.h"
#include "container.h"

namespace s21 {
template <class K, class T>
class map : public container<T> {
 private:
  struct KeyTreeNode;

 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<K, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename bs_tree<KeyTreeNode, key_type, value_type>::iterator;
  using const_iterator =
      typename bs_tree<KeyTreeNode, key_type, value_type>::const_iterator;
  using size_type = size_t;

  map() noexcept = default;
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m) noexcept;

  ~map() noexcept;

  map &operator=(const map &m);
  map &operator=(map &&m) noexcept;

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
  void swap(map &other);
  void merge(map &other);

  bool contains(const key_type &key);

 private:
  struct KeyTreeNode {
   public:
    [[nodiscard]] key_type key() const noexcept;
    KeyTreeNode() noexcept = default;
    KeyTreeNode(value_type value) noexcept;
    value_type value_ = value_type();
  };

  bs_tree<KeyTreeNode, key_type, value_type> tree_ =
      bs_tree<KeyTreeNode, key_type, value_type>();
};

template <class K, class T>
typename map<K, T>::size_type map<K, T>::max_size() const noexcept {
  return tree_.max_size();
}

template <class K, class T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  if (contains(key)) {
    iterator res = tree_.find(key);
    (*res).second = obj;
    return std::pair<iterator, bool>(res, false);
  }
  return insert(key, obj);
}

template <class K, class T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const key_type &key, const mapped_type &obj) {
  if (!contains(key)) {
    value_type value(key, obj);
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::pair<iterator, bool>(tree_.end(), false);
}

template <class K, class T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const map::value_type &value) {
  if (!contains(value.first)) {
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::pair<iterator, bool>(tree_.end(), false);
}

template <class K, class T>
typename map<K, T>::mapped_type &map<K, T>::operator[](const key_type &key) {
  iterator found = tree_.find(key);
  if (found == end()) {
    found = insert(key, mapped_type()).first;
  }

  return (*found).second;
}

template <class K, class T>
typename map<K, T>::mapped_type &map<K, T>::at(const key_type &key) {
  iterator found = tree_.find(key);
  if (found == end()) {
    throw std::out_of_range(
        "Container does not have an element with the specified key");
  }
  return (*found).second;
}

template <class K, class T>
void map<K, T>::merge(map &other) {
  map<K, T> res;
  for (auto elem = other.begin(); elem != other.end(); ++elem) {
    if (!insert(*elem).second) {
      res.insert(*elem);
    }
  }
  other = res;
}

template <class K, class T>
void map<K, T>::swap(map &other) {
  tree_.swap(other.tree_);
}

template <class K, class T>
void map<K, T>::erase(map::iterator pos) {
  tree_.erase(pos);
}

template <class K, class T>
bool map<K, T>::contains(const key_type &key) {
  return tree_.contains(key);
}

template <class K, class T>
typename map<K, T>::size_type map<K, T>::size() const noexcept {
  return tree_.size();
}

template <class K, class T>
bool map<K, T>::empty() const noexcept {
  return size() == 0;
}

template <class K, class T>
typename map<K, T>::iterator map<K, T>::begin() const noexcept {
  return tree_.begin();
}

template <class K, class T>
typename map<K, T>::iterator map<K, T>::end() const noexcept {
  return tree_.end();
}

template <class K, class T>
map<K, T> &map<K, T>::operator=(map &&m) noexcept {
  tree_ = std::move(m.tree_);
  return *this;
}

template <class K, class T>
map<K, T> &map<K, T>::operator=(const map &m) {
  tree_ = m.tree_;
  return *this;
}

template <class K, class T>
map<K, T>::map(map &&m) noexcept {
  *this = std::move(m);
}

template <class K, class T>
map<K, T>::map(const map &m) {
  *this = m;
}

template <class K, class T>
map<K, T>::map(const std::initializer_list<value_type> &items) {
  for (auto elem : items) {
    insert(elem);
  }
}

template <class K, class T>
void map<K, T>::clear() noexcept {
  tree_.clear();
}

template <class K, class T>
map<K, T>::~map() noexcept {
  clear();
}

template <class K, class T>
[[nodiscard]] typename map<K, T>::key_type map<K, T>::KeyTreeNode::key()
    const noexcept {
  return value_.first;
}

template <class K, class T>
map<K, T>::KeyTreeNode::KeyTreeNode(value_type value) noexcept
    : value_(value) {}

}  // namespace s21

#endif  // SRC_SOURCE_MAP_H_
