// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool sets_equal(Set<T> first, Set<T> second) {
  auto first_it = first.begin();
  auto second_it = second.begin();
  for (; first_it != first.end() && second_it != second.end();
       ++first_it, ++second_it) {
    if (*first_it != *second_it) {
      return false;
    }
  }

  return first_it == first.end() && second_it == second.end();
}

TEST(SetSuite, default_contructor_test) {
  Set<int> a;
  ASSERT_EQ(a.size(), 0);
  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(a.begin() == a.end());
}

TEST(SetSuite, initializer_list_constructor_test) {
  Set<int> a = {4, 2, 1, 1};

  ASSERT_EQ(a.size(), 4);
  ASSERT_FALSE(a.empty());
  ASSERT_FALSE(a.begin() == a.end());
}

TEST(SetSuite, copy_constructor_test) {
  Set<int> a = {4, 2, 1, 1};
  Set<int> b(a);

  ASSERT_EQ(b.size(), 4);
  ASSERT_FALSE(b.empty());
  ASSERT_FALSE(b.begin() == b.end());
  ASSERT_TRUE(sets_equal(a, b));
}

TEST(SetSuite, move_constructor_test) {
  Set<int> a = {1, 2, 3};
  Set<int> b(std::move(a));

  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);

  ASSERT_EQ(b.size(), 3);
  ASSERT_FALSE(b.empty());
  ASSERT_FALSE(b.begin() == b.end());
}

TEST(SetSuite, begin_normal_test) {
  Set<int> a = {1};
  ASSERT_EQ(*a.begin(), 1);
}

TEST(SetSuite, end_normal_test) {
  Set<int> a = {1};
  ASSERT_EQ(*(--a.end()), 1);
}

TEST(SetSuite, equal_iterators_test) {
  Set<int> a;
  ASSERT_TRUE(a.begin() == a.end());
}

TEST(SetSuite, empty_list_test) {
  Set<int> a;
  ASSERT_TRUE(a.empty());
}

TEST(SetSuite, non_empty_list_test) {
  Set<int> a = {1, 2, 3};
  ASSERT_FALSE(a.empty());
}

TEST(SetSuite, zero_size_test) {
  Set<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(SetSuite, non_zero_size_test) {
  for (int i = 0; i < 10; ++i) {
    Set<int> a;
    for (int j = 0; j < i; ++j) {
      a.insert(i);
    }
    ASSERT_EQ(a.size(), i);
  }
}

TEST(SetSuite, clear_empty_test) {
  Set<int> a;
  a.clear();
  ASSERT_TRUE(true);  // not sigsegv
}

TEST(SetSuite, clear_non_empty_test) {
  Set<int> a = {1, 2, 3};
  a.clear();

  ASSERT_EQ(a.size(), 0);
  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(a.begin() == a.end());
}

}  // namespace s21
