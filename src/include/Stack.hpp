// Copyright 2023 School-21

#ifndef SRC_INCLUDE_STACK_H_
#define SRC_INCLUDE_STACK_H_

#include "ForwardList.hpp"

namespace s21 {

template <class T>
class Stack : public ForwardList<T> {
 public:
  using value_type = typename ForwardList<T>::value_type;
  using reference = typename ForwardList<T>::reference;
  using const_reference = typename ForwardList<T>::const_reference;
  using size_type = typename ForwardList<T>::size_type;

  Stack() = default;
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &q);
  Stack(Stack &&q) noexcept;
  ~Stack() noexcept override;
  Stack &operator=(const Stack &q);
  Stack &operator=(Stack &&q) noexcept;

  const_reference top() const;

  // inherited empty() and size()

  void push(const_reference value);
  void pop();
  // inherited swap()
};

}  // namespace s21

#endif  // SRC_INCLUDE_STACK_H_
