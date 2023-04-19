// Copyright 2023 School-21

#ifndef SRC_SOURCE_NODE_H_
#define SRC_SOURCE_NODE_H_

#include <stdexcept>

namespace s21 {

template <class T>
class INode {
 public:
  virtual INode *get_next() const noexcept = 0;
  virtual INode *get_prev() const = 0;
  virtual const T &value() const = 0;
  virtual void set_next(INode<T> *ptr) noexcept = 0;
  virtual void set_prev(INode<T> *ptr) = 0;
  virtual T &value() = 0;

  virtual ~INode() noexcept = default;
};

template <class T>
struct UNode : public INode<T> {
 public:
  explicit UNode(T value) : value_(value) {}
  UNode<T> &operator=(const UNode<T> &other) {
    if (this == &other) {
      return *this;
    }

    value_ = other.value_;
    next_ = other.next_;

    return *this;
  }
  UNode(const UNode<T> &other) { *this = other; }
  ~UNode() noexcept override = default;

  INode<T> *get_next() const noexcept override { return next_; }
  INode<T> *get_prev() const override {
    throw std::logic_error("Doesn't exist");
  }
  const T &value() const override { return value_; }
  void set_next(INode<T> *ptr) noexcept override { next_ = ptr; }
  void set_prev(INode<T> *) override {
    throw std::logic_error("Doesn't exist");
  }
  T &value() override { return value_; }

 protected:
  INode<T> *next_ = nullptr;
  T value_ = {};
};

template <class T>
class BiNode : public UNode<T> {
 public:
  explicit BiNode(T value) : UNode<T>(value) {}
  BiNode<T> &operator=(const BiNode<T> &other) {
    if (this == &other) {
      return *this;
    }

    this->value_ = other.value_;
    this->next_ = other.next_;
    this->prev_ = other.prev_;

    return *this;
  }
  BiNode(const BiNode<T> &other) { *this = other; }
  ~BiNode() noexcept override = default;

  INode<T> *get_prev() const noexcept override { return prev_; }
  void set_prev(INode<T> *ptr) noexcept override { prev_ = ptr; }

 private:
  INode<T> *prev_ = nullptr;
};

}  // namespace s21

#endif  // SRC_SOURCE_NODE_H_
