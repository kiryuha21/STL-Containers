// Copyright 2023 School-21

#ifndef SRC_INCLUDE_LIST_H_
#define SRC_INCLUDE_LIST_H_

#include "ForwardList.h"

namespace s21 {

template <class T>
class List : public ForwardList<T> {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = typename ForwardList<T>::value_type;
  using reference = typename ForwardList<T>::reference;
  using const_reference = typename ForwardList<T>::const_reference;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = typename ForwardList<T>::size_type;

  List() = default;
  explicit List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l) noexcept;
  ~List() noexcept override;
  List &operator=(const List &l);
  List &operator=(List &&l) noexcept;

  using ForwardList<T>::front;
  using ForwardList<T>::back;

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  // inherited empty() and size()
  [[nodiscard]] size_type max_size() const noexcept;

  // inherited clear()
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference val) override;
  void pop_back() override;
  void push_front(const_reference val) override;
  void pop_front() override;
  // inherited swap()
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  class ListIterator {
   public:
    explicit ListIterator(INode<T> *node) : node_(node) {}

    iterator &operator--();
    iterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
    reference operator*();

   protected:
    INode<T> *node_ = nullptr;
  };

  class ListConstIterator {
   public:
    explicit ListConstIterator(INode<T> *node) : node_(node) {}

    const_iterator &operator--();
    const_iterator &operator++();
    bool operator==(const_iterator &other);
    bool operator!=(const_iterator &other);
    const_reference operator*();

   protected:
    INode<T> *node_ = nullptr;
  };

 private:
  INode<T> *allocate_node(value_type value) const override;
};

}  // namespace s21

#endif  // SRC_INCLUDE_LIST_H_
