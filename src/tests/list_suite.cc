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

template <class T>
std::ostream& operator<<(std::ostream& os, List<T> list) {
  for (auto& i : list) {
    os << i << " ";
  }
  return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, std::list<T> list) {
  for (auto& i : list) {
    os << i << " ";
  }
  return os;
}

TEST(ListSuite, default_contructor_test) {
  List<int> a;

  ASSERT_EQ(a.size(), 0);
  ASSERT_TRUE(a.empty());
  ASSERT_TRUE(a.cbegin() == a.cend());
  ASSERT_TRUE(a.begin() == a.end());
  ASSERT_THROW(a.front(), std::logic_error);
  ASSERT_THROW(a.back(), std::logic_error);
}

TEST(ListSuite, sized_contructor_test) {
  List<int> a(5);

  ASSERT_EQ(a.size(), 5);
  ASSERT_FALSE(a.empty());
  ASSERT_FALSE(a.cbegin() == a.cend());
  ASSERT_FALSE(a.begin() == a.end());
  ASSERT_EQ(a.front(), a.back());
}

TEST(ListSuite, initializer_list_contructor_test) {
  List<int> a = {1, 2, 3};

  ASSERT_EQ(a.size(), 3);
  ASSERT_FALSE(a.empty());
  ASSERT_FALSE(a.cbegin() == a.cend());
  ASSERT_FALSE(a.begin() == a.end());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 3);
}

TEST(ListSuite, copy_contructor_test) {
  List<int> a = {1, 2, 3};
  List<int> b(a);

  ASSERT_EQ(b.size(), 3);
  ASSERT_FALSE(b.empty());
  ASSERT_FALSE(b.cbegin() == b.cend());
  ASSERT_FALSE(b.begin() == b.end());
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 3);
}

TEST(ListSuite, move_contructor_test) {
  List<int> a = {1, 2, 3};
  List<int> b(std::move(a));

  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
  ASSERT_THROW(a.front(), std::logic_error);

  ASSERT_EQ(b.size(), 3);
  ASSERT_FALSE(b.empty());
  ASSERT_FALSE(b.cbegin() == b.cend());
  ASSERT_FALSE(b.begin() == b.end());
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 3);
}

TEST(ListSuite, normal_front_test) {
  List<int> a = {1, 2, 3};
  ASSERT_EQ(a.front(), 1);
}

TEST(ListSuite, exception_front_test) {
  List<int> a;
  ASSERT_THROW(a.front(), std::logic_error);
}

TEST(ListSuite, normal_back_test) {
  List<int> a = {1, 2, 3};
  ASSERT_EQ(a.back(), 3);
}

TEST(ListSuite, exception_back_test) {
  List<int> a;
  ASSERT_THROW(a.back(), std::logic_error);
}

TEST(ListSuite, begin_normal_test) {
  List<int> a = {1};
  ASSERT_EQ(*a.begin(), 1);
}

TEST(ListSuite, begin_exception_test) {
  List<int> a;
  ASSERT_THROW(*a.begin(), std::logic_error);
}

TEST(ListSuite, end_normal_test) {
  std::list<int> a = {1};
  ASSERT_EQ(*(--a.end()), 1);
}

TEST(ListSuite, end_exception_test) {
  List<int> a;
  ASSERT_THROW(*a.end(), std::logic_error);
}

TEST(ListSuite, cbegin_normal_test) {
  List<int> a = {1};
  ASSERT_EQ(*a.cbegin(), 1);
}

TEST(ListSuite, cbegin_exception_test) {
  List<int> a;
  ASSERT_THROW(*a.cbegin(), std::logic_error);
}

TEST(ListSuite, cend_normal_test) {
  std::list<int> a = {1};
  ASSERT_EQ(*(--a.cend()), 1);
}

TEST(ListSuite, cend_exception_test) {
  List<int> a;
  ASSERT_THROW(*a.cend(), std::logic_error);
}

TEST(ListSuite, empty_list_test) {
  List<int> a;
  ASSERT_TRUE(a.empty());
}

TEST(ListSuite, non_empty_list_test) {
  List<int> a = {1, 2, 3};
  ASSERT_FALSE(a.empty());
}

TEST(ListSuite, zero_size_test) {
  List<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(ListSuite, non_zero_size_test) {
  List<int> a = {1, 2, 3};
  ASSERT_EQ(a.size(), 3);
}

TEST(ListSuite, max_size_test_1) {
  List<int> a;
  std::list<int> b;
  ASSERT_EQ(a.max_size(), b.max_size());
}

TEST(ListSuite, max_size_test_2) {
  List<long double> a;
  std::list<long double> b;
  ASSERT_EQ(a.max_size(), b.max_size());
}

TEST(ListSuite, insert_to_empty_test) {
  List<int> a;
  auto it = a.insert(a.begin(), 1);
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 1);
}

TEST(ListSuite, insert_front_test) {
  List<int> a = {1};
  auto it = a.insert(a.begin(), 2);
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.front(), 2);
}

TEST(ListSuite, insert_back_test) {
  List<int> a = {1};
  auto it = a.insert(a.end(), 2);
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.back(), 2);
}

TEST(ListSuite, insert_mid_test) {
  List<int> a = {1, 2};

  auto it = a.insert(++a.begin(), 3);
  ASSERT_EQ(*it, 3);
  ASSERT_EQ(a.size(), 3);
  ASSERT_TRUE(lists_equal(a, List<int>{1, 3, 2}));
}

TEST(ListSuite, erase_empty_test) {
  List<int> a;
  ASSERT_THROW(a.erase(a.begin()), std::logic_error);
}

TEST(ListSuite, erase_front_test) {
  List<int> a = {1, 2};
  a.erase(a.begin());
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.size(), 1);
}

TEST(ListSuite, erase_back_test) {
  List<int> a = {1, 2};
  a.erase(--a.end());
  ASSERT_EQ(a.back(), 1);
  ASSERT_EQ(a.size(), 1);
}

TEST(ListSuite, erase_mid_test) {
  List<int> a = {1, 2, 3};
  auto it = a.begin();
  ++it;

  a.erase(it);
  ASSERT_EQ(a.size(), 2);
  ASSERT_TRUE(lists_equal(a, List<int>{1, 3}));
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

TEST(ListSuite, pop_back_empty_test) {
  List<int> a;
  ASSERT_THROW(a.pop_back(), std::logic_error);
}

TEST(ListSuite, pop_back_non_empty_test) {
  List<int> a = {1, 2};
  a.pop_back();
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), a.front());
}

TEST(ListSuite, push_front_to_empty_test) {
  List<int> a;
  a.push_front(1);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.front(), a.back());
}

TEST(ListSuite, push_front_to_non_empty_test) {
  List<int> a = {1};
  a.push_front(2);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.back(), 1);
}

TEST(ListSuite, pop_front_empty_test) {
  List<int> a;
  ASSERT_THROW(a.pop_front(), std::logic_error);
}

TEST(ListSuite, pop_front_non_empty_test) {
  List<int> a = {1, 2};
  a.pop_front();
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.back(), a.front());
}

TEST(ListSuite, swap_test) {
  List<int> first_list = {1, 2, 3};
  List<int> second_list = {4, 5, 6};
  List<int> first_copy(first_list);
  List<int> second_copy(second_list);

  first_list.swap(second_list);
  ASSERT_TRUE(lists_equal(first_list, second_copy));
  ASSERT_TRUE(lists_equal(second_list, first_copy));
}

TEST(ListSuite, merge_to_empty) {
  List<int> a;
  List<int> b = {1, 2, 3};

  std::list<int> c;
  std::list<int> d = {1, 2, 3};

  a.merge(b);
  c.merge(d);

  ASSERT_EQ(a.size(), 3);
  ASSERT_TRUE(lists_equal(a, c));
}

TEST(ListSuite, merge_to_back) {
  List<int> a = {4, 5};
  List<int> b = {7, 8, 9};

  std::list<int> c = {4, 5};
  std::list<int> d = {7, 8, 9};

  a.merge(b);
  c.merge(d);

  ASSERT_EQ(a.size(), 5);
  ASSERT_TRUE(lists_equal(a, c));
}

TEST(ListSuite, merge_to_front) {
  List<int> a = {7, 8, 9};
  List<int> b = {4, 5};

  std::list<int> c = {7, 8, 9};
  std::list<int> d = {4, 5};

  a.merge(b);
  c.merge(d);

  ASSERT_EQ(a.size(), 5);
  ASSERT_TRUE(lists_equal(a, c));
}

TEST(ListSuite, merge_to_self) {
  List<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};

  a.merge(a);
  b.merge(b);

  ASSERT_TRUE(lists_equal(a, b));
  ASSERT_TRUE(lists_equal(a, List<int>{1, 2, 3}));
}

TEST(ListSuite, splice_to_empty_test) {
  List<int> my_dest;
  List<int> my_source = {3, 4};

  std::list<int> std_dest;
  std::list<int> std_source = {3, 4};

  my_dest.splice(my_dest.cbegin(), my_source);
  std_dest.splice(std_dest.cbegin(), std_source);

  ASSERT_TRUE(lists_equal(my_dest, std_dest));
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

  my_dest.splice(++my_dest.cbegin(), my_source);
  std_dest.splice(++std_dest.cbegin(), std_source);

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

TEST(ListSuite, reverse_empty_test) {
  List<int> a;
  std::list<int> b;

  a.reverse();
  b.reverse();

  // test that no exceptions occur for empty list
  ASSERT_TRUE(true);
}

TEST(ListSuite, reverse_test) {
  List<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};

  a.reverse();
  b.reverse();

  ASSERT_TRUE(lists_equal(a, b));
  ASSERT_EQ(a.front(), 3);
  ASSERT_EQ(a.back(), 1);
}

TEST(ListSuite, unique_empty_test) {
  List<int> a;
  std::list<int> b;

  a.unique();
  b.unique();

  // test that no exceptions occur for empty list
  ASSERT_TRUE(true);
}

TEST(ListSuite, no_unique_test) {
  List<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};

  a.unique();
  b.unique();

  ASSERT_EQ(a.size(), 3);
  ASSERT_TRUE(lists_equal(a, b));
}

TEST(ListSuite, unique_test) {
  List<int> a = {1, 2, 2, 2, 3, 2, 2};
  std::list<int> b = {1, 2, 2, 2, 3, 2, 2};

  a.unique();
  b.unique();

  std::cout << "a is\n" << a << "\nb is\n" << b << std::endl;

  ASSERT_EQ(a.size(), 4);
  ASSERT_TRUE(lists_equal(a, b));
}

TEST(ListSuite, sort_empty_test) {
  List<int> a;
  std::list<int> b;

  a.sort();
  b.sort();

  // test that no exceptions occur for empty list
  ASSERT_TRUE(true);
}

TEST(ListSuite, no_sort_test) {
  List<int> a = {1, 2, 3};
  std::list<int> b = {1, 2, 3};

  a.sort();
  b.sort();

  ASSERT_EQ(a.size(), 3);
  ASSERT_TRUE(lists_equal(a, b));
}

TEST(ListSuite, sort_test) {
  List<int> a = {1, 2, 1, 5, 4, 12, -5};
  std::list<int> b = {1, 2, 1, 5, 4, 12, -5};

  a.sort();
  b.sort();

  std::cout << "a is\n" << a << "\nb is\n" << b << std::endl;

  ASSERT_EQ(a.size(), 4);
  ASSERT_TRUE(lists_equal(a, b));
}

}  // namespace s21
