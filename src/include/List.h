// Copyright 2023 School-21

#ifndef SRC_INCLUDE_LIST_H_
#define SRC_INCLUDE_LIST_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

#include "Container.h"

namespace s21 {

auto constexpr kEmptyCollectionMsg = "Empty Collection!";

template <class T>
class List : public Container<T> {
 protected:
  struct Node;

 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = typename Container<T>::value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = typename Container<T>::size_type;

  List() = default;
  explicit List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l) noexcept;
  ~List() noexcept override;
  List &operator=(const List &l);
  List &operator=(List &&l) noexcept;

  const_reference front() const;
  const_reference back() const;

  iterator begin() const;
  iterator end() const;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept override;
  [[nodiscard]] size_type max_size() const noexcept;

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other) noexcept;
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  class ListIterator {
   public:
    explicit ListIterator(Node *node) : node_(node) {}

    iterator operator+();
    iterator operator-();
    iterator &operator--();
    iterator &operator++();
    reference operator*();

   private:
    Node *node_ = nullptr;
  };

  class ListConstIterator {
    explicit ListConstIterator(Node *node) : node_(node) {}
    const_iterator operator+();
    const_iterator operator-();
    const_iterator &operator--();
    const_iterator &operator++();
    const_reference operator*();

   private:
    Node *node_ = nullptr;
  };

 protected:
  struct Node {
    value_type value;
    Node *next = nullptr;
    Node *prev = nullptr;

    Node() = default;
    explicit Node(value_type val) : value(val) {}
  };

  Node *head_ = nullptr;
  Node *tail_ = nullptr;

 private:
  void allocate_nodes(size_type size);
};

}  // namespace s21

#endif  // SRC_INCLUDE_LIST_H_
