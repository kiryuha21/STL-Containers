#ifndef SRC_SOURCE_BSTREE_TREENODE_H
#define SRC_SOURCE_BSTREE_TREENODE_H

#include <cstdlib>
#include <utility>

namespace tree_node {
template <class V, class K>  // V must be class(contains node_ and key_type
                             // key()), K - key_type
class TreeNode {
 public:
  class TreeIterator;
  class TreeConstIterator;

  using value_type = V;
  using key_type = K;
  using iterator = TreeIterator;
  using const_iterator = TreeConstIterator;
  using reference = V &;
  using const_reference = const V &;
  using size_type = size_t;

  class TreeIterator {
   public:
    value_type operator*();
    iterator &operator--();
    iterator &operator++();
    iterator &operator-=(size_type count);
    iterator &operator+=(size_type count);
    iterator operator-(size_type count);
    iterator operator+(size_type count);
    bool operator==(const iterator &other) const noexcept;
    bool operator!=(const iterator &other) const noexcept;

    TreeIterator(TreeNode *node, bool end_iterator) noexcept;
    TreeIterator(TreeNode *node) noexcept;
    TreeIterator() noexcept = default;

    TreeNode *get_node() const noexcept;

   private:
    TreeNode *node_ = nullptr;
    bool end_iterator_ = false;
  };

  class TreeConstIterator : public TreeIterator {
    // value_type operator*() override; TODO
  };

  TreeNode() noexcept = default;
  explicit TreeNode(value_type value) noexcept;
  TreeNode(value_type value, TreeNode *parent) noexcept;
  TreeNode(const TreeNode &other);

  TreeNode &operator=(const TreeNode &other);

  ~TreeNode() noexcept;

  [[nodiscard]] size_type size() const noexcept;

  void clear() noexcept;
  iterator insert(const value_type &value);
  void erase(iterator pos);

  iterator find(const key_type &key) noexcept;

  TreeNode *get_left() const noexcept;
  TreeNode *get_right() const noexcept;
  TreeNode *get_parent() const noexcept;
  value_type get_value() const noexcept;

  TreeNode *front() noexcept;
  TreeNode *back() noexcept;

 private:
  value_type value_ = value_type();
  TreeNode *left_ = nullptr;
  TreeNode *right_ = nullptr;
  TreeNode *parent_ = nullptr;

  TreeNode *find_place(const key_type &key) noexcept;
};

template <class V, class K>
typename TreeNode<V, K>::value_type TreeNode<V, K>::iterator::operator*() {
  return end_iterator_ ? value_type() : node_->get_value();
}

// template <class V, class K>
// typename TreeNode<V, K>::value_type
// TreeNode<V, K>::const_iterator::operator*() {
//   // return end_iterator_ ? value_type() : node_->get_value(); TODO
// }

template <class V, class K>
typename TreeNode<V, K>::iterator &TreeNode<V, K>::iterator::operator--() {
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

template <class V, class K>
typename TreeNode<V, K>::iterator &TreeNode<V, K>::iterator::operator++() {
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

template <class V, class K>
typename TreeNode<V, K>::iterator &TreeNode<V, K>::TreeIterator::operator+=(
    TreeNode::size_type count) {
  for (int i = 0; i < count; ++i) {
    ++(*this);
  }

  return *this;
}

template <class V, class K>
typename TreeNode<V, K>::iterator &TreeNode<V, K>::TreeIterator::operator-=(
    TreeNode::size_type count) {
  for (int i = 0; i < count; ++i) {
    --(*this);
  }

  return *this;
}

template <class V, class K>
typename TreeNode<V, K>::iterator TreeNode<V, K>::TreeIterator::operator-(
    TreeNode::size_type count) {
  iterator result = *this;
  result -= count;
  return result;
}

template <class V, class K>
typename TreeNode<V, K>::iterator TreeNode<V, K>::TreeIterator::operator+(
    TreeNode::size_type count) {
  iterator result = *this;
  result += count;
  return result;
}

template <class V, class K>
bool TreeNode<V, K>::iterator::operator==(
    const iterator &other) const noexcept {
  if (end_iterator_ == other.end_iterator_ && end_iterator_ == true) {
    return true;
  }
  return node_ == other.node_ && end_iterator_ == other.end_iterator_;
}

template <class V, class K>
bool TreeNode<V, K>::iterator::operator!=(
    const iterator &other) const noexcept {
  if (end_iterator_ == other.end_iterator_ && end_iterator_ == false) {
    return false;
  }
  return node_ != other.node_ || end_iterator_ != other.end_iterator_;
}

template <class V, class K>
TreeNode<V, K>::TreeIterator::TreeIterator(TreeNode *node,
                                           bool end_iterator) noexcept
    : node_(node), end_iterator_(end_iterator) {}

template <class V, class K>
TreeNode<V, K>::TreeIterator::TreeIterator(TreeNode *node) noexcept
    : node_(node), end_iterator_(node == nullptr) {}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::TreeIterator::get_node() const noexcept {
  return node_;
}

template <class V, class K>
TreeNode<V, K>::TreeNode(value_type value) noexcept : value_(value) {}

template <class V, class K>
TreeNode<V, K>::TreeNode(value_type value, TreeNode *parent) noexcept
    : value_(value), parent_(parent) {}

template <class V, class K>
TreeNode<V, K>::TreeNode(const TreeNode &other) {
  *this = other;
}

template <class V, class K>
TreeNode<V, K> &TreeNode<V, K>::operator=(const TreeNode<V, K> &other) {
  if (this == &other) {
    return *this;
  }

  clear();

  value_ = other.value_;
  if (!left_ && other.left_) {
    left_ = new TreeNode<V, K>;
  }
  left_ = other.left_;
  left_->parent_ = this;

  if (!right_ && other.right_) {
    right_ = new TreeNode<V, K>;
  }
  right_ = other.right_;
  right_->parent_ = this;

  return *this;
}

template <class V, class K>
TreeNode<V, K>::~TreeNode() noexcept {
  delete right_;
  delete left_;
}

template <class V, class K>
[[nodiscard]] typename TreeNode<V, K>::size_type TreeNode<V, K>::size()
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

template <class V, class K>
void TreeNode<V, K>::clear() noexcept {
  if (left_) {
    left_->clear();
  }
  if (right_) {
    right_->clear();
  }
  delete this;
}

template <class V, class K>
typename TreeNode<V, K>::iterator TreeNode<V, K>::insert(
    const value_type &value) {
  if (value_.key() <= value.key()) {
    if (!right_) {
      right_ = new TreeNode<V, K>(value, this);
      return iterator(right_);
    } else {
      return right_->insert(value);
    }
  }

  if (!left_) {
    left_ = new TreeNode<V, K>(value, this);
    return iterator(left_);
  } else {
    return left_->insert(value);
  }
}

template <class V, class K>
void TreeNode<V, K>::erase(iterator pos) {
  TreeNode **child_of = nullptr;
  if (pos.get_node()->parent_) {
    child_of = &(pos.get_node()->parent_->right_ == pos.get_node()
                     ? pos.get_node()->parent_->right_
                     : pos.get_node()->parent_->left_);
  }
  if (!pos.get_node()->left_ && !pos.get_node()->right_) {
    if (child_of) {
      *child_of = nullptr;
    }
    delete pos.get_node();
  } else if (!pos.get_node()->left_) {
    if (child_of) {
      *child_of = pos.get_node()->left_;
    }
    pos.get_node()->left_->parent_ = parent_;
    delete pos.get_node();
  } else if (!pos.get_node()->right_) {
    if (child_of) {
      *child_of = pos.get_node()->right_;
    }
    pos.get_node()->right_->parent_ = parent_;
    delete pos.get_node();
  } else {
    if (!pos.get_node()->right_->left_) {
      TreeNode *swap_with = pos.get_node()->right_;
      if (swap_with->right_) {
        swap_with->right_->parent_ = pos.get_node();
      }
      pos.get_node()->value_ = swap_with->value_;
      pos.get_node()->right_ = swap_with->right_;
      delete swap_with;
    } else {
      TreeNode *leftest = pos.get_node()->right_->left_;
      while (leftest->left_) {
        leftest = leftest->left_;
      }
      pos.get_node()->value_ = leftest->value_;
      erase(iterator(leftest));
    }
  }
}

template <class V, class K>
typename TreeNode<V, K>::iterator TreeNode<V, K>::find(
    const key_type &key) noexcept {
  iterator found = find_place(key);
  if (found.get_node()->value_.key() != key) {
    return nullptr;
  }

  return found;
}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::get_left() const noexcept {
  return left_;
}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::get_right() const noexcept {
  return right_;
}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::get_parent() const noexcept {
  return parent_;
}

template <class V, class K>
typename TreeNode<V, K>::value_type TreeNode<V, K>::get_value() const noexcept {
  return value_;
}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::front() noexcept {
  if (parent_) {
    return parent_->front();
  }
  TreeNode *pointer = this;
  while (pointer->left_) {
    pointer = pointer->left_;
  }
  return pointer;
}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::back() noexcept {
  if (parent_) {
    return parent_->back();
  }
  TreeNode *pointer = this;
  while (pointer->right_) {
    pointer = pointer->right_;
  }
  return pointer;
}

template <class V, class K>
TreeNode<V, K> *TreeNode<V, K>::find_place(const key_type &key) noexcept {
  if (value_.key() < key && right_ != nullptr) {
    return right_->find_place(key);
  } else if (value_.key() > key && left_ != nullptr) {
    return left_->find_place(key);
  }
  return this;
}

}  // namespace tree_node

#endif  // SRC_SOURCE_BSTREE_TREENODE_H
