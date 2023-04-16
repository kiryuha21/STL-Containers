#ifndef CPP2_S21_CONTAINERS_1_QUEUE_H
#define CPP2_S21_CONTAINERS_1_QUEUE_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "Container.h"

namespace s21 {
auto constexpr kEmptyQueueMsg = "Empty Queue!";

template <class T>
class Queue : public Container<T> {
 public:
  using value_type = typename Container<T>::value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using size_type = typename Container<T>::size_type;

  Queue() = default;
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue() noexcept override;
  Queue &operator=(const Queue &q);
  Queue &operator=(Queue &&q) noexcept;

  const_reference front() const;
  const_reference back() const;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept override;

  void push(const_reference value);
  void pop();
  void swap(Queue &other);

 private:
  void clear();

  struct Node {
    value_type value;
    Node *next = nullptr;

    explicit Node(value_type val) : value(val){};
  };

  Node *head_ = nullptr;
  Node *tail_ = nullptr;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_QUEUE_H
