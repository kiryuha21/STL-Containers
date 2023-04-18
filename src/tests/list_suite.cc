// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool lists_equal(List<T> first, List<T> second) {
  auto i = first.cbegin();
  auto j = second.cbegin();
  for (; i != first.cend() && j != second.cend(); ++i, ++j) {
    if (*i != *j) {
      return false;
    }
  }

  return i == first.cend() && j == second.cend();
}

template <class T>
bool lists_equal(List<T> first, std::list<T> second) {
  auto i = first.cbegin();
  auto j = second.cbegin();
  for (; i != first.cend() && j != second.cend(); ++i, ++j) {
    if (*i != *j) {
      return false;
    }
  }

  return i == first.cend() && j == second.cend();
}

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

TEST(ListSuite, splice_at_begin_test) {
  List<int> my_dest = {1, 2};
  List<int> my_source = {3, 4};

  std::list<int> std_dest = {1, 2};
  std::list<int> std_source = {3, 4};

  my_dest.splice(my_dest.cbegin(), my_source);
  std_dest.splice(std_dest.cbegin(), std_source);

  ASSERT_TRUE(lists_equal(my_dest, std_dest));
}

TEST(ListSuite, splice_at_middle_test) {
  List<int> my_dest = {1, 2};
  List<int> my_source = {3, 4};

  std::list<int> std_dest = {1, 2};
  std::list<int> std_source = {3, 4};

  auto my_it = my_dest.cbegin();
  auto std_it = std_dest.cbegin();
  ++my_it;
  ++std_it;

  my_dest.splice(my_it, my_source);
  std_dest.splice(std_it, std_source);

  ASSERT_TRUE(lists_equal(my_dest, std_dest));
}

TEST(ListSuite, splice_at_end_test) {
  List<int> my_dest = {1, 2};
  List<int> my_source = {3, 4};

  std::list<int> std_dest = {1, 2};
  std::list<int> std_source = {3, 4};

  my_dest.splice(my_dest.cend(), my_source);
  std_dest.splice(std_dest.cend(), std_source);

  ASSERT_TRUE(lists_equal(my_dest, std_dest));
}

}  // namespace s21
