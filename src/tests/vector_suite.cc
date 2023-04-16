// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_containers.h"

template <class T>
bool vectors_equal(const std::vector<T> &std_res,
                   const s21::Vector<T> &my_res) {
  if (my_res.size() != std_res.size()) {
    std::cout << "std_res size = " << std_res.size()
              << ", my_res size = " << my_res.size() << "\n";
    return false;
  }

  if (my_res.capacity() != std_res.capacity()) {
    std::cout << "std_res capacity = " << std_res.capacity()
              << ", my_res capacity = " << my_res.capacity() << "\n";
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

TEST(VectorSuite, 1_initial_list) {
  s21::Vector<int> my_res = {1, 2, 3};
  std::vector<int> std_res = {1, 2, 3};
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_THROW(my_res.at(3), std::out_of_range);
}

TEST(VectorSuite, 2_default_constructors) {
  s21::Vector<int> my_res(16);
  std::vector<int> std_res(16);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_THROW(my_res.at(30), std::out_of_range);
}

TEST(VectorSuite, 3_max_size) {
  s21::Vector<int> my_res;
  std::vector<int> std_res;
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_EQ(my_res.max_size(), std_res.max_size());
}

TEST(VectorSuite, 4_push_pop_back) {
  s21::Vector<int> my_res;
  std::vector<int> std_res;
  my_res.push_back(3);
  std_res.push_back(3);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  my_res.pop_back();
  std_res.pop_back();
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 5_clear) {
  s21::Vector<int> my_res = {4, 3};
  std::vector<int> std_res = {4, 3};
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  my_res.clear();
  std_res.clear();
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 6_insert) {
  s21::Vector<int> my_res({1, 2, 3});
  std::vector<int> std_res({1, 2, 3});
  ASSERT_EQ(my_res.front(), std_res.front());
  ASSERT_EQ(my_res.back(), std_res.back());
}

TEST(VectorSuite, 7_insert) {
  s21::Vector<int> my_res({2});
  std::vector<int> std_res({2});
  std_res.insert(std_res.begin(), 1);
  my_res.insert(my_res.begin(), 1);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 8_erase) {
  s21::Vector<int> my_res = {2};
  std::vector<int> std_res = {2};
  std_res.erase(std_res.begin());
  my_res.erase(my_res.begin());
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 9_erase) {
  s21::Vector<int> my_res = {3, 4, 5};
  std::vector<int> std_res = {3, 4, 5};
  std_res.erase(std_res.begin());
  my_res.erase(my_res.begin());
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 10_many_changes) {
  s21::Vector<int> my_res = {3, 4, 5, 6, 4, 5};
  std::vector<int> std_res = {3, 4, 5, 6, 4, 5};
  std_res.erase(std_res.begin() + 3);
  my_res.erase(my_res.begin() + 3);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  std_res.insert(std_res.begin() + 3, 10);
  my_res.insert(my_res.begin() + 3, 10);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 11_insert) {
  s21::Vector<int> my_res;
  std::vector<int> std_res;
  std_res.insert(std_res.begin(), 10);
  my_res.insert(my_res.begin(), 10);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 12_erase) {
  s21::Vector<int> my_res;
  ASSERT_THROW(my_res.erase(my_res.begin()), std::out_of_range);
}

TEST(VectorSuite, 13_constructors) {
  s21::Vector<int> my_res;
  std::vector<int> std_res;
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 14_constructors) {
  s21::Vector<int> my_res(10);
  std::vector<int> std_res(10);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 15_constructors) {
  s21::Vector<int> my_res({});
  std::vector<int> std_res({});
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 16_constructors) {
  s21::Vector<int> my_res({3, 4});
  std::vector<int> std_res({3, 4});
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 17_constructors) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_res(my_vec);
  std::vector<int> std_res(std_vec);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, 18_constructors) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_res(std::move(my_vec));
  std::vector<int> std_res(std::move(std_vec));
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}
