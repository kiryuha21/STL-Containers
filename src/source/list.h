// Copyright 2023 School-21

#ifndef SRC_SOURCE_LIST_H_
#define SRC_SOURCE_LIST_H_

#include <utility>

#include "forward_list.h"

namespace s21 {

template <class T>
class list : public forward_list<T> {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = typename forward_list<T>::value_type;
  using reference = typename forward_list<T>::reference;
  using const_reference = typename forward_list<T>::const_reference;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = typename forward_list<T>::size_type;

  list() = default;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list() noexcept override;
  list &operator=(const list &l);
  list &operator=(list &&l) noexcept;

  using forward_list<T>::front;
  using forward_list<T>::back;

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  // inherited empty() and size()
  [[nodiscard]] size_type max_size() const noexcept;

  using forward_list<T>::clear;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference val) override;
  void pop_back() override;
  void push_front(const_reference val) override;
  void pop_front() override;
  // inherited swap()
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  class ListIterator {
   public:
    ListIterator() = default;
    ListIterator(list_node<T> *node, list_node<T> *head, list_node<T> *tail)
        : node_(node), head_(head), tail_(tail) {}
    list_node<T> *get_node() const { return node_; }
    void set_node(list_node<T> *node) { node_ = node; }

    iterator &operator--();
    iterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
    reference operator*();

   private:
    list_node<T> *node_ = nullptr;
    list_node<T> *head_ = nullptr;
    list_node<T> *tail_ = nullptr;
  };

  class ListConstIterator {
   public:
    ListConstIterator() = default;
    ListConstIterator(list_node<T> *node, list_node<T> *head,
                      list_node<T> *tail)
        : node_(node), head_(head), tail_(tail) {}
    list_node<T> *get_node() const { return node_; }
    void set_node(list_node<T> *node) { node_ = node; }

    const_iterator &operator--();
    const_iterator &operator++();
    bool operator==(const const_iterator &other);
    bool operator!=(const const_iterator &other);
    const_reference operator*();

   private:
    list_node<T> *node_ = nullptr;
    list_node<T> *head_ = nullptr;
    list_node<T> *tail_ = nullptr;
  };

 private:
  list_node<T> *allocate_node(value_type value) const override;
};

template <class T>
list<T>::list(list::size_type n) {
  for (size_type i = 0; i < n; ++i) {
    this->push_back({});
  }
}

template <class T>
list<T>::list(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    this->push_back(i);
  }
}

template <class T>
list<T>::list(const list &l) : list<T>() {
  *this = l;
}

template <class T>
list<T>::list(list &&l) noexcept {
  *this = std::move(l);
}

template <class T>
list<T>::~list() noexcept {
  this->clear();
}

template <class T>
list<T> &list<T>::operator=(const list &l) {
  if (this == &l) {
    return *this;
  }

  this->clear();
  for (list_node<T> *temp = l.head_; temp != nullptr; temp = temp->get_next()) {
    push_back(temp->value());
  }

  return *this;
}

template <class T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this == &l) {
    return *this;
  }

  this->clear();

  this->head_ = std::exchange(l.head_, nullptr);
  this->tail_ = std::exchange(l.tail_, nullptr);
  this->size_ = std::exchange(l.size_, 0);

  return *this;
}

template <class T>
typename list<T>::iterator list<T>::begin() const {
  return iterator(this->head_, this->head_, this->tail_);
}

template <class T>
typename list<T>::iterator list<T>::end() const {
  if (this->empty()) {
    return iterator(this->tail_, this->head_, this->tail_);
  }
  return iterator(this->tail_->get_next(), this->head_, this->tail_);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(this->head_, this->head_, this->tail_);
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const {
  if (this->empty()) {
    return const_iterator(this->tail_, this->head_, this->tail_);
  }
  return const_iterator(this->tail_->get_next(), this->head_, this->tail_);
}

template <class T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return size_type(-1) / sizeof(binary_node<T>);
}

template <class T>
typename list<T>::iterator list<T>::insert(list::iterator pos,
                                           const_reference value) {
  if (pos == begin()) {
    push_front(value);
    return iterator(this->head_, this->head_, this->tail_);
  }

  if (pos == end()) {
    push_back(value);
    return iterator(this->tail_, this->head_, this->tail_);
  }

  list_node<T> *temp = pos.get_node()->get_prev();
  list_node<T> *new_node = allocate_node(value);

  new_node->set_next(pos.get_node());
  pos.get_node()->set_prev(new_node);

  new_node->set_prev(temp);
  temp->set_next(new_node);

  ++this->size_;
  return iterator(new_node, this->head_, this->tail_);
}

template <class T>
void list<T>::erase(list::iterator pos) {
  if (pos.get_node() == nullptr) {
    throw std::logic_error("attempt to delete nullptr!");
  }

  if (pos.get_node() == this->head_) {
    this->pop_front();
    return;
  }

  if (pos.get_node() == this->tail_) {
    this->pop_back();
    return;
  }

  list_node<T> *next = pos.get_node()->get_next();
  list_node<T> *prev = pos.get_node()->get_prev();

  prev->set_next(next);
  next->set_prev(prev);

  --this->size_;
  delete pos.get_node();
}

template <class T>
void list<T>::push_back(const_reference val) {
  list_node<T> *temp = this->tail_;
  forward_list<T>::push_back(val);
  if (this->head_ != this->tail_) {
    this->tail_->set_prev(temp);
  }
}

template <class T>
void list<T>::pop_back() {
  if (this->tail_ == nullptr) {
    throw std::logic_error(kEmptyCollectionMsg);
  }

  --this->size_;
  this->tail_ = this->tail_->get_prev();
  delete this->tail_->get_next();
  this->tail_->set_next(nullptr);
}

template <class T>
void list<T>::push_front(const_reference val) {
  list_node<T> *temp = this->head_;
  forward_list<T>::push_front(val);
  if (this->head_ != this->tail_) {
    temp->set_prev(this->head_);
  }
}

template <class T>
void list<T>::pop_front() {
  forward_list<T>::pop_front();
  this->head_->set_prev(nullptr);
}

template <class T>
void list<T>::merge(list &other) {
  if (this == &other) {
    return;
  }

  if (this->empty() || other.front() > this->back()) {
    splice(this->cend(), other);
  } else {
    splice(this->cbegin(), other);
  }
}

template <class T>
void list<T>::splice(list::const_iterator pos, list &other) {
  if (other.empty()) {
    return;
  }

  if (this->empty()) {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
  } else if (pos == cend()) {
    other.head_->set_prev(this->tail_);
    this->tail_->set_next(other.head_);
    this->tail_ = other.tail_;
  } else if (pos == cbegin()) {
    other.tail_->set_next(this->head_);
    this->head_->set_prev(other.tail_);
    this->head_ = other.head_;
  } else {
    list_node<T> *new_next = pos.get_node();
    list_node<T> *new_prev = (--pos).get_node();

    other.head_->set_prev(new_prev);
    new_prev->set_next(other.head_);

    other.tail_->set_next(new_next);
    new_next->set_prev(other.tail_);
  }

  this->size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <class T>
void list<T>::reverse() {
  for (auto i = this->head_; i != nullptr; i = i->get_prev()) {
    list_node<T> *temp = i->get_next();
    i->set_next(i->get_prev());
    i->set_prev(temp);
  }
  std::swap(this->head_, this->tail_);
}

template <class T>
void list<T>::unique() {
  if (this->empty()) {
    return;
  }

  auto backward = this->begin();
  auto forward = ++this->begin();
  for (; forward != this->end(); backward = forward, ++forward) {
    if (*forward == *backward) {
      erase(backward);
    }
  }
}

template <class T>
void list<T>::sort() {
  if (this->empty()) {
    return;
  }

  for (list_node<T> *i = this->head_; i->get_next() != nullptr;
       i = i->get_next()) {
    for (list_node<T> *j = i->get_next(); j != nullptr; j = j->get_next()) {
      if (i->value() > j->value()) {
        std::swap(i->value(), j->value());
      }
    }
  }
}

template <class T>
typename list<T>::iterator &list<T>::ListIterator::operator--() {
  if (get_node() == nullptr) {
    set_node(tail_);
  } else {
    set_node(get_node()->get_prev());
  }
  return *this;
}

template <class T>
typename list<T>::iterator &list<T>::ListIterator::operator++() {
  if (get_node() == nullptr) {
    set_node(head_);
  } else {
    set_node(get_node()->get_next());
  }
  return *this;
}

template <class T>
bool list<T>::ListIterator::operator==(const iterator &other) {
  return get_node() == other.get_node();
}

template <class T>
bool list<T>::ListIterator::operator!=(const iterator &other) {
  return get_node() != other.get_node();
}

template <class T>
typename list<T>::reference list<T>::ListIterator::operator*() {
  if (get_node() == nullptr) {
    throw std::logic_error("nullptr dereference!");
  }
  return get_node()->value();
}

template <class T>
typename list<T>::const_iterator &list<T>::ListConstIterator::operator--() {
  if (get_node() == nullptr) {
    set_node(tail_);
  } else {
    set_node(get_node()->get_prev());
  }
  return *this;
}

template <class T>
typename list<T>::const_iterator &list<T>::ListConstIterator::operator++() {
  if (get_node() == nullptr) {
    set_node(head_);
  } else {
    set_node(get_node()->get_next());
  }
  return *this;
}

template <class T>
bool list<T>::ListConstIterator::operator==(const const_iterator &other) {
  return get_node() == other.get_node();
}

template <class T>
bool list<T>::ListConstIterator::operator!=(const const_iterator &other) {
  return get_node() != other.get_node();
}

template <class T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*() {
  if (get_node() == nullptr) {
    throw std::logic_error("nullptr dereference!");
  }
  return get_node()->value();
}

template <class T>
list_node<T> *list<T>::allocate_node(value_type value) const {
  list_node<T> *new_node = nullptr;

  try {
    new_node = new binary_node<T>(value);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  return new_node;
}

}  // namespace s21

#endif  // SRC_SOURCE_LIST_H_
