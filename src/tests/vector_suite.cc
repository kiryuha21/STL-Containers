// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool vectors_equal(const std::vector<T> &std_res,
                   const s21::Vector<T> &my_res) {
  if (my_res.size() != std_res.size()) {
    std::cout << "std_res size = " << std_res.size()
              << ", my_res size = " << my_res.size() << "\n";
    return false;
  }
  size_t size = my_res.size();
  for (size_t i = 0; i < size; ++i) {
    if (my_res.data()[i] != std_res.data()[i]) {
      std::cout << "std_res[" << i << "]: " << std_res.data()[i] << ", my_res["
                << i << "]: " << my_res.data()[i] << "\n";
      return false;
    }
  }
  return true;
}
TEST(Vector, 1_vectors_initial_list) {
  Vector<int> my_res = {1, 2, 3};
  std::vector<int> std_res = {1, 2, 3};
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_THROW(my_res.at(3), std::out_of_range);
}

TEST(Vector, 2_vectors_default_constructors) {
  Vector<int> my_res(16);
  std::vector<int> std_res(16);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_THROW(my_res.at(30), std::out_of_range);
}

TEST(Vector, 3_vectors_max_size) {
  Vector<int> my_res;
  std::vector<int> std_res;
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_EQ(my_res.max_size(), std_res.max_size());
}

TEST(Vector, 4_vectors_push_pop_back) {
  Vector<int> my_res;
  std::vector<int> std_res;
  my_res.push_back(3);
  std_res.push_back(3);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  my_res.pop_back();
  std_res.pop_back();
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(Vector, 5_vectors_clear) {
  Vector<int> my_res = {4, 3};
  std::vector<int> std_res = {4, 3};
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  my_res.clear();
  std_res.clear();
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(Vector, 6_vectors_insert) {
  Vector<int> my_res = {1, 2, 3};
  std::vector<int> std_res = {1, 2, 3};
  ASSERT_EQ(my_res.front(), std_res.front());
  ASSERT_EQ(my_res.back(), std_res.back());
  my_res = {1};
  std_res = {1};
  ASSERT_EQ(my_res.front(), std_res.front());
  ASSERT_EQ(my_res.back(), std_res.back());
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(Vector, 7_vectors_insert) {
  Vector<int> my_res = {2};
  std::vector<int> std_res = {2};
  std_res.insert(std_res.begin(), 1);
  my_res.insert(my_res.begin(), 1);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(Vector, 8_vectors_erase) {
  Vector<int> my_res = {2};
  std::vector<int> std_res = {2};
  std_res.erase(std_res.begin());
  my_res.erase(my_res.begin());
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(Vector, 9_vectors_erase) {
  Vector<int> my_res = {3, 4, 5};
  std::vector<int> std_res = {3, 4, 5};
  std_res.erase(std_res.begin());
  my_res.erase(my_res.begin());
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(Vector, 10_vectors_many_changes) {
  Vector<int> my_res = {3, 4, 5, 6, 4, 5};
  std::vector<int> std_res = {3, 4, 5, 6, 4, 5};
  std_res.erase(std_res.begin() + 3);
  my_res.erase(my_res.begin() + 3);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  std_res.insert(std_res.begin() + 3, 10);
  my_res.insert(my_res.begin() + 3, 10);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

}  // namespace s21
