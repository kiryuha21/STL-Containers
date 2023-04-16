#ifndef CPP2_S21_CONTAINERS_1_QUEUE_H
#define CPP2_S21_CONTAINERS_1_QUEUE_H

#include <cstdlib>
#include <initializer_list>
#include <stdexcept>
#include <utility>

auto constexpr kEmptyQueueMsg = "Empty Queue!";

namespace s21 {

// TODO: add noexcept
template <class T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() = default;
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q) noexcept;
  ~Queue();
  Queue &operator=(const Queue &q);
  Queue &operator=(Queue &&q) noexcept;

  const_reference front() const;
  const_reference back() const;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(Queue &other);

 private:
  void clear();

  struct Node {
    value_type value;
    reference next = nullptr;
  };

  Node *head_ = nullptr;
  Node *tail_ = nullptr;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_QUEUE_H
