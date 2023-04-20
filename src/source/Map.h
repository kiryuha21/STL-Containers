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
  using iterator = typename bstree::BSTree<KeyTreeNode, key_type>::iterator;
  using const_iterator =
      typename bstree::BSTree<KeyTreeNode, key_type>::const_iterator;
  using size_type = size_t;

  Map() noexcept = default;

 private:
  struct KeyTreeNode {
   public:
    [[nodiscard]] value_type key() const noexcept;
    KeyTreeNode() noexcept = default;
    KeyTreeNode(value_type value) noexcept;

   private:
    value_type value_ = value_type();
  };

  bstree::BSTree<KeyTreeNode, key_type> tree_ =
      bstree::BSTree<KeyTreeNode, key_type>();
};

template <class K, class T>
[[nodiscard]] typename Map<K, T>::value_type Map<K, T>::KeyTreeNode::key()
    const noexcept {
  return value_[1];
}

template <class K, class T>
Map<K, T>::KeyTreeNode::KeyTreeNode(value_type value) noexcept
    : value_(value) {}

}  // namespace s21

#endif  // SRC_SOURCE_MAP_H_
