// Copyright 2023 school-21

#include <gtest/gtest.h>

#include "s21_containers.h"

namespace s21 {
TEST(Vector, 1_shift_left_test) {
  Vector<int> a;
  a = {1, 2, 3};
  ASSERT_EQ(a.at(0), 1);
  ASSERT_EQ(a.at(1), 2);
  ASSERT_EQ(a.at(2), 3);
  ASSERT_THROW(a.at(3), std::out_of_range);
}
}  // namespace s21

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}