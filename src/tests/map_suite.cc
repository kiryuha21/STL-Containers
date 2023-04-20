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
    if ((*first_it).first != (*second_it).first ||
        (*first_it).second != (*second_it).second) {
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
  ASSERT_EQ(*my_map.begin(), std::make_pair(1, std::string("aaa")));
}

TEST(MapSuite, end_normal_test) {
  Map<int, std::string> my_map = {{1, "aaa"}};
  ASSERT_EQ(*(--my_map.end()), std::make_pair(1, std::string("aaa")));
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
      my_map.insert(j, "a");
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
  Map<int, int> my_map = {{1, 2}, {2, 3}, {5, 12}};
  my_map.clear();

  ASSERT_EQ(my_map.size(), 0);
  ASSERT_TRUE(my_map.empty());
  ASSERT_TRUE(my_map.begin() == my_map.end());
}

TEST(MapSuite, insert_to_empty_test) {
  Map<int, int> my_map;
  auto res = my_map.insert({3, 3});
  ASSERT_TRUE(res.second);
  ASSERT_EQ((*(res.first)).first, 3);
  ASSERT_TRUE(maps_equal(my_map, std::map<int, int>{{3, 3}}));
}

TEST(MapSuite, insert_to_non_empty_test) {
  Map<int, int> a = {{1, 1}};
  auto res = a.insert({2, 1});
  ASSERT_TRUE(res.second);
  ASSERT_EQ((*(res.first)).first, 2);
  ASSERT_TRUE(maps_equal(a, std::map<int, int>{{1, 1}, {2, 1}}));
}

TEST(MapSuite, fail_insert_test) {
  Map<int, int> a = {{1, 2}};
  auto res = a.insert({1, 3});
  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first, a.end());
  ASSERT_TRUE(maps_equal(a, std::map<int, int>{{1, 2}}));
}

TEST(MapSuite, erase_empty_test) {
  Map<int, int> a;
  ASSERT_THROW(a.erase(a.begin()), std::out_of_range);
}

TEST(MapSuite, erase_start_test) {
  Map<int, int> a = {{1, 2}, {2, 3}};
  a.erase(a.begin());

  ASSERT_EQ(*a.begin(), (std::pair<int, int>(2, 3)));
  ASSERT_TRUE(maps_equal(a, std::map<int, int>{{2, 3}}));
}

TEST(MapSuite, erase_end_test) {
  Map<int, int> a = {{1, 2}, {2, 3}};
  a.erase(--a.end());

  ASSERT_EQ(*a.begin(), (std::pair<int, int>(1, 2)));
  ASSERT_TRUE(maps_equal(a, std::map<int, int>{{1, 2}}));
}

TEST(MapSuite, erase_mid_test) {
  Map<int, int> a = {{1, 1}, {2, 2}, {3, 3}};
  a.erase(++a.begin());

  ASSERT_EQ(*a.begin(), (std::pair<int, int>{1, 1}));
  ASSERT_EQ(*(--a.end()), (std::pair<int, int>{3, 3}));
  ASSERT_TRUE(maps_equal(a, std::map<int, int>{{1, 1}, {3, 3}}));
}

TEST(MapSuite, swap_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}, {3, 3}};
  Map<int, int> second_map = {{4, 4}, {5, 5}, {6, 6}};
  Map<int, int> first_copy(first_map);
  Map<int, int> second_copy(second_map);

  first_map.swap(second_map);
  ASSERT_TRUE(maps_equal(first_map, second_copy));
  ASSERT_TRUE(maps_equal(second_map, first_copy));
}

TEST(MapSuite, merge_empty_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}, {3, 3}};
  Map<int, int> second_map;

  first_map.merge(second_map);
  ASSERT_TRUE(
      maps_equal(first_map, std::map<int, int>{{1, 1}, {2, 2}, {3, 3}}));
}

TEST(MapSuite, merge_to_empty_test) {
  Map<int, int> first_map;
  Map<int, int> second_map = {{1, 1}, {2, 2}, {3, 3}};

  first_map.merge(second_map);
  ASSERT_TRUE(
      maps_equal(first_map, std::map<int, int>{{1, 1}, {2, 2}, {3, 3}}));
  ASSERT_TRUE(maps_equal(second_map, std::map<int, int>{}));
}

TEST(MapSuite, merge_non_repeating_test) {
  Map<int, int> first_map = {{4, 4}, {5, 5}, {6, 6}};
  Map<int, int> second_map = {{1, 1}, {2, 2}, {3, 3}};

  first_map.merge(second_map);
  ASSERT_TRUE(maps_equal(
      first_map,
      std::map<int, int>{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}));
  ASSERT_TRUE(maps_equal(second_map, std::map<int, int>{}));
}

TEST(MapSuite, merge_repeating_test) {
  Map<int, int> first_map = {{4, 4}, {5, 5}, {6, 6}};
  Map<int, int> second_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};

  first_map.merge(second_map);
  ASSERT_TRUE(maps_equal(
      first_map,
      std::map<int, int>{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}));
  ASSERT_TRUE(maps_equal(second_map, std::map<int, int>{{4, 4}}));
}

TEST(MapSuite, contains_in_empty_test) {
  Map<int, int> first_map;
  auto res = first_map.contains(5);
  ASSERT_FALSE(res);
}

TEST(MapSuite, contains_present_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}, {3, 3}};
  auto res = first_map.contains(2);
  ASSERT_TRUE(res);
}

TEST(MapSuite, contains_non_present_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}, {3, 3}};
  auto res = first_map.contains(4);
  ASSERT_FALSE(res);
}

TEST(MapSuite, access_operator_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> second_map = {{1, 1}, {2, 2}, {3, 3}};
  second_map[1] = 3;
  first_map[1] = 3;
  ASSERT_TRUE(maps_equal(first_map, second_map));
}

TEST(MapSuite, access_operator_empty_test) {
  Map<int, int> first_map;
  std::map<int, int> second_map;
  second_map[1] = 3;
  first_map[1] = 3;
  ASSERT_TRUE(maps_equal(first_map, second_map));
}

TEST(MapSuite, access_at_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> second_map = {{1, 1}, {2, 2}, {3, 3}};
  second_map.at(1) = 3;
  first_map.at(1) = 3;
  ASSERT_TRUE(maps_equal(first_map, second_map));
}

TEST(MapSuite, access_at_empty_test) {
  Map<int, int> first_map;
  ASSERT_THROW(first_map.at(1) = 3, std::out_of_range);
}

TEST(MapSuite, access_at_not_existing_test) {
  Map<int, int> first_map = {{2, 3}};
  ASSERT_THROW(first_map.at(1) = 3, std::out_of_range);
}

TEST(MapSuite, insert_or_assign_insert_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}};
  auto res = first_map.insert_or_assign(3, 4);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*(res.first), (std::pair<int, int>(3, 4)));
  std::map<int, int> second_map = {{1, 1}, {2, 2}};
  second_map.insert_or_assign(3, 4);
  ASSERT_TRUE(maps_equal(first_map, second_map));
}

TEST(MapSuite, insert_or_assign_assert_test) {
  Map<int, int> first_map = {{1, 1}, {2, 2}};
  auto res = first_map.insert_or_assign(2, 3);
  ASSERT_FALSE(res.second);
  ASSERT_EQ(*(res.first), (std::pair<int, int>(2, 3)));
  std::map<int, int> second_map = {{1, 1}, {2, 2}};
  second_map.insert_or_assign(2, 3);
  ASSERT_TRUE(maps_equal(first_map, second_map));
}

TEST(MapSuite, insert_or_assign_empty_test) {
  Map<int, int> first_map;
  auto res = first_map.insert_or_assign(1, 1);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*(res.first), (std::pair<int, int>(1, 1)));
  std::map<int, int> second_map;
  second_map.insert_or_assign(1, 1);
  ASSERT_TRUE(maps_equal(first_map, second_map));
}

}  // namespace s21
