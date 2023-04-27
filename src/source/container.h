// Copyright 2023 School-21

#ifndef SRC_SOURCE_CONTAINER_H_
#define SRC_SOURCE_CONTAINER_H_

#include <cstdlib>

namespace s21 {

template <class T>
class container {
 public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Essential functions
  virtual ~container() noexcept = default;

  // Main functions
  [[nodiscard]] virtual bool empty() const noexcept = 0;
  [[nodiscard]] virtual size_type size() const noexcept = 0;
};

}  // namespace s21

#endif  // SRC_SOURCE_CONTAINER_H_
