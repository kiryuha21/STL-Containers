// Copyright 2023 school-21

#ifndef SRC_SOURCE_TREENODE_H_
#define SRC_SOURCE_TREENODE_H_

#include <cstdlib>
#include <utility>

namespace s21 {
template <class V, class K, class T>  // V must be class(contains node_ and
                                      // key_type key()), K - key_type
class tree_node {
 public:
  class TreeIterator;
  class TreeConstIterator;

  using value_type = V;
  using key_type = K;
  using obj_type = T;
  using iterator = TreeIterator;
  using const_iterator = TreeConstIterator;
  using reference = V &;
  using const_reference = const V &;
  using size_type = size_t;

  class TreeIterator {
   public:
    obj_type &operator*();
    iterator &operator--();
    iterator &operator++();
    iterator &operator-=(size_type count);
    iterator &operator+=(size_type count);
    iterator operator-(size_type count);
    iterator operator+(size_type count);
    bool operator==(const iterator &other) const noexcept;
    bool operator!=(const iterator &other) const noexcept;

    TreeIterator(tree_node *node, bool end_iterator) noexcept;
    TreeIterator(tree_node *node) noexcept;
    TreeIterator() noexcept = default;

    tree_node *get_node() const noexcept;

   private:
    tree_node *node_ = nullptr;
    bool end_iterator_ = false;
  };

  class TreeConstIterator : public TreeIterator {
    const obj_type &operator*();

   private:
    tree_node *node_ = nullptr;
    bool end_iterator_ = false;
  };

  tree_node() noexcept = default;
  explicit tree_node(value_type value) noexcept;
  tree_node(value_type value, tree_node *parent) noexcept;
  tree_node(const tree_node &other);

  tree_node &operator=(const tree_node &other);

  ~tree_node() noexcept;

  [[nodiscard]] size_type size() const noexcept;

  void clear() noexcept;
  iterator insert(const value_type &value);
  void erase(iterator pos);

  iterator find(const key_type &key) noexcept;

  tree_node *get_left() const noexcept;
  tree_node *get_right() const noexcept;
  tree_node *get_parent() const noexcept;
  value_type &get_value() noexcept;

  tree_node *front() noexcept;
  tree_node *back() noexcept;

 private:
  value_type value_ = value_type();
  tree_node *left_ = nullptr;
  tree_node *right_ = nullptr;
  tree_node *parent_ = nullptr;

  tree_node *find_place(const key_type &key) noexcept;
};

template <class V, class K, class T>
typename tree_node<V, K, T>::obj_type &
tree_node<V, K, T>::iterator::operator*() {
  return node_->get_value().value_;
}

template <class V, class K, class T>
const typename tree_node<V, K, T>::obj_type &
tree_node<V, K, T>::TreeConstIterator::operator*() {
  return node_->get_value().value_;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator &
tree_node<V, K, T>::iterator::operator--() {
  if (end_iterator_) {
    end_iterator_ = false;
    node_ = node_->back();
  } else if (node_ == node_->front()) {
    end_iterator_ = true;
  } else if (node_->get_left() != nullptr) {
    node_ = node_->get_left();
    while (node_->get_right()) {
      node_ = node_->get_right();
    }
  } else {
    while (node_->get_parent() && node_->get_parent()->get_left() == node_) {
      node_ = node_->get_parent();
    }
    if (node_->get_parent() && node_ == node_->get_parent()->get_right()) {
      node_ = node_->get_parent();
    }
  }

  return *this;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator &
tree_node<V, K, T>::iterator::operator++() {
  if (end_iterator_) {
    end_iterator_ = false;
    node_ = node_->back();
  } else if (node_ == node_->back()) {
    end_iterator_ = true;
  } else if (node_->get_right() != nullptr) {
    node_ = node_->get_right();
    while (node_->get_left()) {
      node_ = node_->get_left();
    }
  } else {
    while (node_->get_parent() && node_->get_parent()->get_right() == node_) {
      node_ = node_->get_parent();
    }
    if (node_->get_parent() && node_ == node_->get_parent()->get_left()) {
      node_ = node_->get_parent();
    }
  }

  return *this;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator &
tree_node<V, K, T>::TreeIterator::operator+=(tree_node::size_type count) {
  for (int i = 0; i < count; ++i) {
    ++(*this);
  }

  return *this;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator &
tree_node<V, K, T>::TreeIterator::operator-=(tree_node::size_type count) {
  for (int i = 0; i < count; ++i) {
    --(*this);
  }

  return *this;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator
tree_node<V, K, T>::TreeIterator::operator-(tree_node::size_type count) {
  iterator result = *this;
  result -= count;
  return result;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator
tree_node<V, K, T>::TreeIterator::operator+(tree_node::size_type count) {
  iterator result = *this;
  result += count;
  return result;
}

template <class V, class K, class T>
bool tree_node<V, K, T>::iterator::operator==(
    const iterator &other) const noexcept {
  if (end_iterator_ == other.end_iterator_ && end_iterator_ == true) {
    return true;
  }
  return node_ == other.node_ && end_iterator_ == other.end_iterator_;
}

template <class V, class K, class T>
bool tree_node<V, K, T>::iterator::operator!=(
    const iterator &other) const noexcept {
  if (end_iterator_ == other.end_iterator_ && end_iterator_ == false) {
    return false;
  }
  return node_ != other.node_ || end_iterator_ != other.end_iterator_;
}

template <class V, class K, class T>
tree_node<V, K, T>::TreeIterator::TreeIterator(tree_node *node,
                                               bool end_iterator) noexcept
    : node_(node), end_iterator_(end_iterator) {}

template <class V, class K, class T>
tree_node<V, K, T>::TreeIterator::TreeIterator(tree_node *node) noexcept
    : node_(node), end_iterator_(node == nullptr) {}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::TreeIterator::get_node()
    const noexcept {
  return node_;
}

template <class V, class K, class T>
tree_node<V, K, T>::tree_node(value_type value) noexcept : value_(value) {}

template <class V, class K, class T>
tree_node<V, K, T>::tree_node(value_type value, tree_node *parent) noexcept
    : value_(value), parent_(parent) {}

template <class V, class K, class T>
tree_node<V, K, T>::tree_node(const tree_node &other) {
  *this = other;
}

template <class V, class K, class T>
tree_node<V, K, T> &tree_node<V, K, T>::operator=(
    const tree_node<V, K, T> &other) {
  if (this == &other) {
    return *this;
  }

  clear();

  value_ = other.value_;
  if (!left_ && other.left_) {
    left_ = new tree_node<V, K, T>;
  }
  left_ = other.left_;
  left_->parent_ = this;

  if (!right_ && other.right_) {
    right_ = new tree_node<V, K, T>;
  }
  right_ = other.right_;
  right_->parent_ = this;

  return *this;
}

template <class V, class K, class T>
tree_node<V, K, T>::~tree_node() noexcept {
  delete right_;
  delete left_;
}

template <class V, class K, class T>
[[nodiscard]] typename tree_node<V, K, T>::size_type tree_node<V, K, T>::size()
    const noexcept {
  size_type result = 1;
  if (left_) {
    result += left_->size();
  }
  if (right_) {
    result += right_->size();
  }
  return result;
}

template <class V, class K, class T>
void tree_node<V, K, T>::clear() noexcept {
  if (left_) {
    left_->clear();
  }
  if (right_) {
    right_->clear();
  }
  delete this;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator tree_node<V, K, T>::insert(
    const value_type &value) {
  if (value_.key() <= value.key()) {
    if (!right_) {
      right_ = new tree_node<V, K, T>(value, this);
      return iterator(right_);
    } else {
      return right_->insert(value);
    }
  }

  if (!left_) {
    left_ = new tree_node<V, K, T>(value, this);
    return iterator(left_);
  } else {
    return left_->insert(value);
  }
}

template <class V, class K, class T>
void tree_node<V, K, T>::erase(iterator pos) {
  if (!pos.get_node()->left_ && !pos.get_node()->right_) {
    if (pos.get_node()->parent_) {
      if (pos.get_node()->parent_->right_ == pos.get_node()) {
        pos.get_node()->parent_->right_ = nullptr;
      } else {
        pos.get_node()->parent_->left_ = nullptr;
      }
    }
    delete pos.get_node();
  } else if (!pos.get_node()->left_) {
    tree_node *swap_with = pos.get_node()->right_;
    pos.get_node()->left_ = swap_with->left_;
    pos.get_node()->right_ = swap_with->right_;
    if (pos.get_node()->left_) {
      pos.get_node()->left_->parent_ = pos.get_node();
    }
    if (pos.get_node()->right_) {
      pos.get_node()->right_->parent_ = pos.get_node();
    }
    pos.get_node()->value_ = swap_with->get_value();
    swap_with->left_ = swap_with->right_ = nullptr;
    delete swap_with;
  } else if (!pos.get_node()->right_) {
    tree_node *swap_with = pos.get_node()->left_;
    pos.get_node()->left_ = swap_with->left_;
    pos.get_node()->right_ = swap_with->right_;
    if (pos.get_node()->left_) {
      pos.get_node()->left_->parent_ = pos.get_node();
    }
    if (pos.get_node()->right_) {
      pos.get_node()->right_->parent_ = pos.get_node();
    }
    pos.get_node()->value_ = swap_with->get_value();
    swap_with->left_ = swap_with->right_ = nullptr;
    delete swap_with;
  } else {
    if (!pos.get_node()->right_->left_) {
      tree_node *swap_with = pos.get_node()->right_;
      if (swap_with->right_) {
        swap_with->right_->parent_ = pos.get_node();
      }
      pos.get_node()->value_ = swap_with->value_;
      pos.get_node()->right_ = swap_with->right_;
      delete swap_with;
    } else {
      tree_node *leftest = pos.get_node()->right_->left_;
      while (leftest->left_) {
        leftest = leftest->left_;
      }
      pos.get_node()->value_ = leftest->value_;
      erase(iterator(leftest));
    }
  }
}

template <class V, class K, class T>
typename tree_node<V, K, T>::iterator tree_node<V, K, T>::find(
    const key_type &key) noexcept {
  iterator found = find_place(key);
  if (found.get_node()->value_.key() != key) {
    return nullptr;
  }

  return found;
}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::get_left() const noexcept {
  return left_;
}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::get_right() const noexcept {
  return right_;
}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::get_parent() const noexcept {
  return parent_;
}

template <class V, class K, class T>
typename tree_node<V, K, T>::value_type &
tree_node<V, K, T>::get_value() noexcept {
  return value_;
}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::front() noexcept {
  if (parent_) {
    return parent_->front();
  }
  tree_node *pointer = this;
  while (pointer->left_) {
    pointer = pointer->left_;
  }
  return pointer;
}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::back() noexcept {
  if (parent_) {
    return parent_->back();
  }
  tree_node *pointer = this;
  while (pointer->right_) {
    pointer = pointer->right_;
  }
  return pointer;
}

template <class V, class K, class T>
tree_node<V, K, T> *tree_node<V, K, T>::find_place(
    const key_type &key) noexcept {
  if (value_.key() < key && right_ != nullptr) {
    return right_->find_place(key);
  } else if (value_.key() > key && left_ != nullptr) {
    return left_->find_place(key);
  }
  return this;
}

}  // namespace s21

#endif  // SRC_SOURCE_TREENODE_H_
