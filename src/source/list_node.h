// Copyright 2023 School-21

#ifndef SRC_SOURCE_NODE_H_
#define SRC_SOURCE_NODE_H_

#include <stdexcept>

namespace s21 {

template <class T>
class list_node {
 public:
  virtual list_node *get_next() const noexcept = 0;
  virtual list_node *get_prev() const = 0;
  virtual const T &value() const = 0;
  virtual void set_next(list_node<T> *ptr) noexcept = 0;
  virtual void set_prev(list_node<T> *ptr) = 0;
  virtual T &value() = 0;

  virtual ~list_node() noexcept = default;
};

template <class T>
struct unary_node : public list_node<T> {
 public:
  explicit unary_node(T value) : value_(value) {}
  unary_node<T> &operator=(const unary_node<T> &other) {
    if (this == &other) {
      return *this;
    }

    value_ = other.value_;
    next_ = other.next_;

    return *this;
  }
  unary_node(const unary_node<T> &other) { *this = other; }
  ~unary_node() noexcept override = default;

  list_node<T> *get_next() const noexcept override { return next_; }
  list_node<T> *get_prev() const override {
    throw std::logic_error("Doesn't exist");
  }
  const T &value() const override { return value_; }
  void set_next(list_node<T> *ptr) noexcept override { next_ = ptr; }
  void set_prev(list_node<T> *) override {
    throw std::logic_error("Doesn't exist");
  }
  T &value() override { return value_; }

 protected:
  list_node<T> *next_ = nullptr;
  T value_ = {};
};

template <class T>
class binary_node : public unary_node<T> {
 public:
  explicit binary_node(T value) : unary_node<T>(value) {}
  binary_node<T> &operator=(const binary_node<T> &other) {
    if (this == &other) {
      return *this;
    }

    this->value_ = other.value_;
    this->next_ = other.next_;
    this->prev_ = other.prev_;

    return *this;
  }
  binary_node(const binary_node<T> &other) { *this = other; }
  ~binary_node() noexcept override = default;

  list_node<T> *get_prev() const noexcept override { return prev_; }
  void set_prev(list_node<T> *ptr) noexcept override { prev_ = ptr; }

 private:
  list_node<T> *prev_ = nullptr;
};

}  // namespace s21

#endif  // SRC_SOURCE_NODE_H_
