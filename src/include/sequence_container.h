// Copyright 2023 school-21
#ifndef SRC_INCLUDE_SEQUENCE_CONTAINER_H_
#define SRC_INCLUDE_SEQUENCE_CONTAINER_H_

#include <cstdlib>

#include "./container.h"

namespace s21 {

// TODO(guinicyb): for vector and list in UML but ...
template <class T>
class SequenceContainer : public Container {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;  // TODO(guinicyb): should be diff for vector and list
  using const_iterator = const T *;
  using size_type = size_t;
};
}  // namespace s21

#endif  // SRC_INCLUDE_SEQUENCE_CONTAINER_H_
