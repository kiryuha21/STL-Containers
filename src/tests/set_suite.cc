// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"

namespace s21 {
TEST(SetSuite, initializer_list_constructor) {
  Set<int> my_set({4, 2, 1, 1});
  my_set.find(3);
}

}  // namespace s21
