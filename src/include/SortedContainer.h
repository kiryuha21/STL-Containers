// Copyright 2023 school-21

#ifndef SRC_SORTEDCONTAINER_H
#define SRC_SORTEDCONTAINER_H

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

}  // namespace s21

#endif  // SRC_SORTEDCONTAINER_H
