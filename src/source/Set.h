#ifndef SRC_SOURCE_SET_H_
#define SRC_SOURCE_SET_H_

#include "BSTree.h"

namespace s21 {

template <class V>
class Set {  // TODO: public Container
 private:
  class SetNodeValue;

 public:
  using value_type = V;
  using key_type = V;
  using iterator = typename bstree::BSTree<SetNodeValue, key_type>::iterator;
  using const_iterator =
      typename bstree::BSTree<SetNodeValue, key_type>::const_iterator;
  using reference = V &;
  using const_reference = const V &;
  using size_type = size_t;

  Set() noexcept = default;
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &other) noexcept;
  Set(Set &&other) noexcept;
  Set &operator=(const Set &s);
  Set &operator=(Set &&s);

  ~Set() noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;
  [[nodiscard]] size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(Set &other) noexcept;
  void merge(Set &other);

  iterator find(const key_type &key) const noexcept;
  [[nodiscard]] bool contains(const key_type &key) const noexcept;

 private:
  class SetNodeValue {
   public:
    [[nodiscard]] value_type key() const noexcept;
    SetNodeValue() noexcept = default;
    SetNodeValue(value_type value) noexcept;

   private:
    value_type value_ = value_type();
  };

  bstree::BSTree<SetNodeValue, key_type> tree_ =
      bstree::BSTree<SetNodeValue, key_type>();
};

template <class V>
bool Set<V>::contains(const key_type &key) const noexcept {
  return tree_.contains(key);
}

template <class V>
typename Set<V>::iterator Set<V>::find(const key_type &key) const noexcept {
  return tree_.find(key);
}

template <class V>
[[nodiscard]] typename Set<V>::value_type Set<V>::SetNodeValue::key()
    const noexcept {
  return value_;
}

template <class V>
Set<V>::SetNodeValue::SetNodeValue(value_type value) noexcept : value_(value) {}

template <class V>
std::pair<typename Set<V>::iterator, bool> Set<V>::insert(
    const value_type &value) {
  if (!contains(value)) {
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::make_pair<iterator, bool>(tree_.end(), false);
}

template <class V>
Set<V>::Set(std::initializer_list<value_type> const &items) {
  for (auto elem : items) {
    insert(elem);
  }
}

}  // namespace s21
#endif  // SRC_SOURCE_SET_H_
