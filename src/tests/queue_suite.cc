// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

namespace s21 {

TEST(QueueSuite, default_constructor) {
  std::queue<int> a;
  Queue<int> b;
  ASSERT_EQ(a.size(), b.size());
}

TEST(QueueSuite, initializer_constructor) {
  std::queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);

  Queue<int> b = {1, 2, 3};

  ASSERT_EQ(a.front(), b.front());
  ASSERT_EQ(a.back(), b.back());
  a.pop();
  b.pop();
  ASSERT_EQ(a.front(), b.front());
}

}  // namespace s21
