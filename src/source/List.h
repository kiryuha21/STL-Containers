// Copyright 2023 School-21

#ifndef SRC_SOURCE_LIST_H_
#define SRC_SOURCE_LIST_H_

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
    ListIterator() = default;
    ListIterator(INode<T> *node, INode<T> *head, INode<T> *tail)
        : node_(node), head_(head), tail_(tail) {}
    INode<T> *get_node() const { return node_; }
    void set_node(INode<T> *node) { node_ = node; }

    iterator &operator--();
    iterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);
    reference operator*();

   private:
    INode<T> *node_ = nullptr;
    INode<T> *head_ = nullptr;
    INode<T> *tail_ = nullptr;
  };

  class ListConstIterator {
   public:
    ListConstIterator() = default;
    ListConstIterator(INode<T> *node, INode<T> *head, INode<T> *tail)
        : node_(node), head_(head), tail_(tail) {}
    INode<T> *get_node() const { return node_; }
    void set_node(INode<T> *node) { node_ = node; }

    const_iterator &operator--();
    const_iterator &operator++();
    bool operator==(const const_iterator &other);
    bool operator!=(const const_iterator &other);
    const_reference operator*();

   private:
    INode<T> *node_ = nullptr;
    INode<T> *head_ = nullptr;
    INode<T> *tail_ = nullptr;
  };

 private:
  INode<T> *allocate_node(value_type value) const override;
};

template <class T>
List<T>::List(List::size_type n) {
  for (size_type i = 0; i < n; ++i) {
    this->push_back({});
  }
}

template <class T>
List<T>::List(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    this->push_back(i);
  }
}

template <class T>
List<T>::List(const List &l) : List<T>() {
  *this = l;
}

template <class T>
List<T>::List(List &&l) noexcept {
  *this = std::move(l);
}

template <class T>
List<T>::~List() noexcept {
  this->clear();
}

template <class T>
List<T> &List<T>::operator=(const List &l) {
  if (this == &l) {
    return *this;
  }

  this->clear();
  for (INode<T> *temp = l.head_; temp != nullptr; temp = temp->get_next()) {
    push_back(temp->value());
  }

  return *this;
}

template <class T>
List<T> &List<T>::operator=(List &&l) noexcept {
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
typename List<T>::iterator List<T>::begin() const {
  return iterator(this->head_, this->head_, this->tail_);
}

template <class T>
typename List<T>::iterator List<T>::end() const {
  if (this->empty()) {
    return iterator(this->tail_, this->head_, this->tail_);
  }
  return iterator(this->tail_->get_next(), this->head_, this->tail_);
}

template <class T>
typename List<T>::const_iterator List<T>::cbegin() const {
  return const_iterator(this->head_, this->head_, this->tail_);
}

template <class T>
typename List<T>::const_iterator List<T>::cend() const {
  if (this->empty()) {
    return const_iterator(this->tail_, this->head_, this->tail_);
  }
  return const_iterator(this->tail_->get_next(), this->head_, this->tail_);
}

template <class T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return size_type(-1) / sizeof(BiNode<T>);
}

template <class T>
typename List<T>::iterator List<T>::insert(List::iterator pos,
                                           const_reference value) {
  if (pos == begin()) {
    push_front(value);
    return iterator(this->head_, this->head_, this->tail_);
  }

  if (pos == end()) {
    push_back(value);
    return iterator(this->tail_, this->head_, this->tail_);
  }

  INode<T> *temp = pos.get_node()->get_prev();
  INode<T> *new_node = allocate_node(value);

  new_node->set_next(pos.get_node());
  pos.get_node()->set_prev(new_node);

  new_node->set_prev(temp);
  temp->set_next(new_node);

  ++this->size_;
  return iterator(new_node, this->head_, this->tail_);
}

template <class T>
void List<T>::erase(List::iterator pos) {
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

  INode<T> *next = pos.get_node()->get_next();
  INode<T> *prev = pos.get_node()->get_prev();

  prev->set_next(next);
  next->set_prev(prev);

  --this->size_;
  delete pos.get_node();
}

template <class T>
void List<T>::push_back(const_reference val) {
  INode<T> *temp = this->tail_;
  ForwardList<T>::push_back(val);
  if (this->head_ != this->tail_) {
    this->tail_->set_prev(temp);
  }
}

template <class T>
void List<T>::pop_back() {
  if (this->tail_ == nullptr) {
    throw std::logic_error(kEmptyCollectionMsg);
  }

  --this->size_;
  this->tail_ = this->tail_->get_prev();
  delete this->tail_->get_next();
  this->tail_->set_next(nullptr);
}

template <class T>
void List<T>::push_front(const_reference val) {
  INode<T> *temp = this->head_;
  ForwardList<T>::push_front(val);
  if (this->head_ != this->tail_) {
    temp->set_prev(this->head_);
  }
}

template <class T>
void List<T>::pop_front() {
  ForwardList<T>::pop_front();
  this->head_->set_prev(nullptr);
}

template <class T>
void List<T>::merge(List &other) {
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
void List<T>::splice(List::const_iterator pos, List &other) {
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
    INode<T> *new_next = pos.get_node();
    INode<T> *new_prev = (--pos).get_node();

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
void List<T>::reverse() {
  for (auto i = this->head_; i != nullptr; i = i->get_prev()) {
    INode<T> *temp = i->get_next();
    i->set_next(i->get_prev());
    i->set_prev(temp);
  }
  std::swap(this->head_, this->tail_);
}

template <class T>
void List<T>::unique() {
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
void List<T>::sort() {
  if (this->empty()) {
    return;
  }

  for (INode<T> *i = this->head_; i->get_next() != nullptr; i = i->get_next()) {
    for (INode<T> *j = i->get_next(); j != nullptr; j = j->get_next()) {
      if (i->value() > j->value()) {
        std::swap(i->value(), j->value());
      }
    }
  }
}

template <class T>
typename List<T>::iterator &List<T>::ListIterator::operator--() {
  if (get_node() == nullptr) {
    set_node(tail_);
  } else {
    set_node(get_node()->get_prev());
  }
  return *this;
}

template <class T>
typename List<T>::iterator &List<T>::ListIterator::operator++() {
  if (get_node() == nullptr) {
    set_node(head_);
  } else {
    set_node(get_node()->get_next());
  }
  return *this;
}

template <class T>
bool List<T>::ListIterator::operator==(const iterator &other) {
  return get_node() == other.get_node();
}

template <class T>
bool List<T>::ListIterator::operator!=(const iterator &other) {
  return get_node() != other.get_node();
}

template <class T>
typename List<T>::reference List<T>::ListIterator::operator*() {
  if (get_node() == nullptr) {
    throw std::logic_error("nullptr dereference!");
  }
  return get_node()->value();
}

template <class T>
typename List<T>::const_iterator &List<T>::ListConstIterator::operator--() {
  if (get_node() == nullptr) {
    set_node(tail_);
  } else {
    set_node(get_node()->get_prev());
  }
  return *this;
}

template <class T>
typename List<T>::const_iterator &List<T>::ListConstIterator::operator++() {
  if (get_node() == nullptr) {
    set_node(head_);
  } else {
    set_node(get_node()->get_next());
  }
  return *this;
}

template <class T>
bool List<T>::ListConstIterator::operator==(const const_iterator &other) {
  return get_node() == other.get_node();
}

template <class T>
bool List<T>::ListConstIterator::operator!=(const const_iterator &other) {
  return get_node() != other.get_node();
}

template <class T>
typename List<T>::const_reference List<T>::ListConstIterator::operator*() {
  if (get_node() == nullptr) {
    throw std::logic_error("nullptr dereference!");
  }
  return get_node()->value();
}

template <class T>
INode<T> *List<T>::allocate_node(value_type value) const {
  INode<T> *new_node = nullptr;

  try {
    new_node = new BiNode<T>(value);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  return new_node;
}

}  // namespace s21

#endif  // SRC_SOURCE_LIST_H_
