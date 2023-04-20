// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <map>

#include "../s21_containers.h"

namespace s21 {

template <class K, class V>
bool maps_equal(Map<K, V> first, std::map<K, V> second) {
  if (first.size() != second.size()) {
    return false;
  }
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

template <class K, class V>
bool maps_equal(Map<K, V> first, Map<K, V> second) {
  if (first.size() != second.size()) {
    return false;
  }
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

TEST(MapSuite, default_contructor_test) {
  Map<int, std::string> my_map;
  std::map<int, std::string> std_map;
  ASSERT_TRUE(my_map.empty());
  ASSERT_TRUE(maps_equal(my_map, std_map));
}

TEST(MapSuite, initializer_list_constructor_test) {
  Map<int, std::string> my_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
  std::map<int, std::string> std_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};

  ASSERT_TRUE(maps_equal(my_map, std_map));
}

TEST(MapSuite, copy_constructor_test) {
  Map<int, std::string> my_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
  Map<int, std::string> my_copied(my_map);
  std::map<int, std::string> std_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};

  ASSERT_TRUE(maps_equal(my_copied, std_map));
}

TEST(MapSuite, move_constructor_test) {
  Map<int, std::string> my_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
  Map<int, std::string> my_moved(std::move(my_map));
  std::map<int, std::string> std_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
  std::map<int, std::string> std_moved(std::move(std_map));
  ASSERT_TRUE(maps_equal(my_moved, std_moved));
  ASSERT_TRUE(maps_equal(my_map, std_map));
}

TEST(MapSuite, begin_normal_test) {
  Map<int, std::string> my_map = {{1, "aaa"}};
  ASSERT_EQ(*my_map.begin(), std::make_pair(1, "aaa"));
}

TEST(MapSuite, end_normal_test) {
  Map<int, std::string> my_map = {{1, "aaa"}};
  ASSERT_EQ(*(--my_map.end()), std::make_pair(1, "aaa"));
}

TEST(MapSuite, equal_iterators_test) {
  Map<int, std::string> my_map;
  ASSERT_TRUE(my_map.begin() == my_map.end());
}

TEST(MapSuite, empty_list_test) {
  Map<int, std::string> my_map;
  ASSERT_TRUE(my_map.empty());
}

TEST(MapSuite, non_empty_list_test) {
  Map<int, std::string> my_map = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}};
  ASSERT_FALSE(my_map.empty());
}

TEST(MapSuite, zero_size_test) {
  Map<int, std::string> my_map;
  ASSERT_EQ(my_map.size(), 0);
}

TEST(MapSuite, non_zero_size_test) {
  for (int i = 0; i < 10; ++i) {
    Map<int, std::string> my_map;
    for (int j = 0; j < i; ++j) {
      my_map.insert(j);
    }
    ASSERT_EQ(my_map.size(), i);
  }
}

TEST(MapSuite, clear_empty_test) {
  Map<int, std::string> my_map;
  my_map.clear();
  ASSERT_TRUE(true);  // not sigsegv
}

TEST(MapSuite, clear_non_empty_test) {
  Map<int, std::string> my_map = {1, 2, 3};
  my_map.clear();

  ASSERT_EQ(my_map.size(), 0);
  ASSERT_TRUE(my_map.empty());
  ASSERT_TRUE(my_map.begin() == my_map.end());
}

TEST(MapSuite, insert_to_empty_test) {
  Map<int, std::string> a;
  auto res = a.insert(1);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*(res.first), 1);
  ASSERT_TRUE(maps_equal(a, std::map{1}));
}

TEST(MapSuite, insert_to_non_empty_test) {
  Map<int, std::string> a = {1};
  auto res = a.insert(2);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*(res.first), 2);
  ASSERT_TRUE(maps_equal(a, std::map{1, 2}));
}

TEST(MapSuite, fail_insert_test) {
  Map<int, std::string> a = {1};
  auto res = a.insert(1);
  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first, a.end());
  ASSERT_TRUE(maps_equal(a, std::map{1}));
}

TEST(MapSuite, erase_empty_test) {
  Map<int, std::string> a;
  ASSERT_THROW(a.erase(a.begin()), std::out_of_range);
}

TEST(MapSuite, erase_start_test) {
  Map<int, std::string> a = {1, 2};
  a.erase(a.begin());

  ASSERT_EQ(*a.begin(), 2);
  ASSERT_TRUE(maps_equal(a, std::map<int, std::string>{2}));
}

TEST(MapSuite, erase_end_test) {
  Map<int, std::string> a = {1, 2};

  ASSERT_THROW(a.erase(a.end()), std::out_of_range);
}

TEST(MapSuite, erase_mid_test) {
  Map<int, std::string> a = {1, 2, 3};
  a.erase(++a.begin());

  ASSERT_EQ(*a.begin(), 1);
  ASSERT_EQ(*(--a.end()), 3);
  ASSERT_TRUE(maps_equal(a, std::map<int, std::string>{1, 3}));
}

TEST(MapSuite, swap_test) {
  Map<int, std::string> first_map = {1, 2, 3};
  Map<int, std::string> second_map = {4, 5, 6};
  Map<int, std::string> first_copy(first_map);
  Map<int, std::string> second_copy(second_map);

  first_map.swap(second_map);
  ASSERT_TRUE(maps_equal(first_map, second_copy));
  ASSERT_TRUE(maps_equal(second_map, first_copy));
}

TEST(MapSuite, merge_empty_test) {
  Map<int, std::string> first_map = {1, 2, 3};
  Map<int, std::string> second_map;

  first_map.merge(second_map);
  ASSERT_TRUE(maps_equal(first_map, std::map{1, 2, 3}));
}

TEST(MapSuite, merge_to_empty_test) {
  Map<int, std::string> first_map;
  Map<int, std::string> second_map = {1, 2, 3};

  first_map.merge(second_map);
  ASSERT_TRUE(maps_equal(first_map, std::map{1, 2, 3}));
  ASSERT_TRUE(maps_equal(second_map, std::map<int, std::string>{}));
}

TEST(MapSuite, merge_non_repeating_test) {
  Map<int, std::string> first_map = {4, 5, 6};
  Map<int, std::string> second_map = {1, 2, 3};

  first_map.merge(second_map);
  ASSERT_TRUE(maps_equal(first_map, std::map{1, 2, 3, 4, 5, 6}));
  ASSERT_TRUE(maps_equal(second_map, std::map<int, std::string>{}));
}

TEST(MapSuite, merge_repeating_test) {
  Map<int, std::string> first_map = {4, 1, 2};
  Map<int, std::string> second_map = {1, 2, 3};

  first_map.merge(second_map);
  ASSERT_TRUE(maps_equal(first_map, std::map{1, 2, 3, 4}));
  ASSERT_TRUE(maps_equal(second_map, std::map<int, std::string>{1, 2}));
}

TEST(MapSuite, find_in_empty_test) {
  Map<int, std::string> first_map;
  auto res = first_map.find(5);
  ASSERT_EQ(res, first_map.end());
}

TEST(MapSuite, find_present_test) {
  Map<int, std::string> first_map = {1, 2, 3};
  auto res = first_map.find(2);
  ASSERT_EQ(*res, 2);
}

TEST(MapSuite, find_non_present_test) {
  Map<int, std::string> first_map = {1, 2, 3};
  auto res = first_map.find(4);
  ASSERT_EQ(res, first_map.end());
}

TEST(MapSuite, contains_in_empty_test) {
  Map<int, std::string> first_map;
  bool res = first_map.contains(5);
  ASSERT_EQ(res, false);
}

TEST(MapSuite, contains_present_test) {
  Map<int, std::string> first_map = {1, 2, 3};
  bool res = first_map.contains(2);
  ASSERT_EQ(res, true);
}

TEST(MapSuite, contains_non_present_test) {
  Map<int, std::string> first_map = {1, 2, 3};
  bool res = first_map.contains(4);
  ASSERT_EQ(res, false);
}

}  // namespace s21
