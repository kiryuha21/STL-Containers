#ifndef CPP2_S21_CONTAINERS_1_CONTAINER_H
#define CPP2_S21_CONTAINERS_1_CONTAINER_H

#include <cstdlib>

template <class T>
class Container {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  [[nodiscard]] virtual size_type size() const noexcept = 0;

  virtual ~Container() noexcept = default;
};

#endif  // CPP2_S21_CONTAINERS_1_CONTAINER_H
