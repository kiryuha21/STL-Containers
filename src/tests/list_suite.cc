// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

namespace s21 {
TEST(ListSuite, push_back_to_empty_test) {
  List<int> a;
  a.push_back(1);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.front(), a.back());
}

TEST(ListSuite, push_back_to_non_empty_test) {
  List<int> a = {1};
  a.push_back(2);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 2);
}
}  // namespace s21
