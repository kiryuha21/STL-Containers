#ifndef CPP2_S21_CONTAINERS_1_STACK_H
#define CPP2_S21_CONTAINERS_1_STACK_H

#include "List.h"

namespace s21 {

template <class T>
class Stack : public List<T> {
 public:
  using value_type = typename Container<T>::value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using size_type = typename Container<T>::size_type;

  Stack() = default;
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &q);
  Stack(Stack &&q) noexcept;
  ~Stack() noexcept override;
  Stack &operator=(const Stack &q);
  Stack &operator=(Stack &&q) noexcept;

  const_reference top() const;

  void push(const_reference value);
  void pop();

 private:
  using Node = typename List<T>::Node;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_STACK_H
