// Copyright 2023 School-21

#ifndef SRC_INCLUDE_CONTAINER_H_
#define SRC_INCLUDE_CONTAINER_H_

#include <cstdlib>

template <class T>
class Container {
 public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Essential functions
  virtual ~Container() noexcept = default;

  // Main functions
  [[nodiscard]] virtual bool empty() const noexcept = 0;
  [[nodiscard]] virtual size_type size() const noexcept = 0;
};

#endif  // SRC_INCLUDE_CONTAINER_H_
