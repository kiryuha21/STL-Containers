// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_containers.h"

template <class T>
bool vectors_equal(const std::vector<T> &std_vec,
                   const s21::Vector<T> &my_vec) {
  if (my_vec.size() != std_vec.size()) {
    std::cout << "std_vec size = " << std_vec.size()
              << ", my_vec size = " << my_vec.size() << "\n";
    return false;
  }

  if (my_vec.capacity() != std_vec.capacity()) {
    std::cout << "std_vec capacity = " << std_vec.capacity()
              << ", my_vec capacity = " << my_vec.capacity() << "\n";
    return false;
  }

  size_t size = my_vec.size();
  for (size_t i = 0; i < size; ++i) {
    if (my_vec.data()[i] != std_vec.data()[i]) {
      std::cout << "std_vec[" << i << "]: " << std_vec.data()[i] << ", my_vec["
                << i << "]: " << my_vec.data()[i] << "\n";
      return false;
    }
  }
  return true;
}

TEST(VectorSuite, def_constructors) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, size_constructors) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, empty_initial_list_constructors) {
  s21::Vector<int> my_vec({});
  std::vector<int> std_vec({});
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, initial_list_constructors) {
  s21::Vector<int> my_vec({3, 4});
  std::vector<int> std_vec({3, 4});
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, copy_constructors) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_vec2;
  std::vector<int> std_vec2;
  ASSERT_TRUE(vectors_equal(std_vec2, my_vec2));
  s21::Vector<int> my_res(my_vec);
  std::vector<int> std_res(std_vec);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  s21::Vector<int> my_res2(my_vec2);
  std::vector<int> std_res2(std_vec2);
  ASSERT_TRUE(vectors_equal(std_res2, my_res2));
}

TEST(VectorSuite, move_constructors) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_res(std::move(my_vec));
  std::vector<int> std_res(std::move(std_vec));
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, copy_assigment) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_res = my_vec;
  std::vector<int> std_res = std_vec;
  ASSERT_TRUE(vectors_equal(std_res, my_res));
}

TEST(VectorSuite, move_assigment) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_res = std::move(my_vec);
  std::vector<int> std_res = std::move(std_vec);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, at_empty) {
  s21::Vector<int> my_vec;
  ASSERT_THROW(my_vec.at(0), std::out_of_range);
}

TEST(VectorSuite, at_out_if_boundes) {
  s21::Vector<int> my_vec(4);
  ASSERT_THROW(my_vec.at(10), std::out_of_range);
}

TEST(VectorSuite, at) {
  s21::Vector<int> my_vec({1, 2, 3, 4});
  std::vector<int> std_vec({1, 2, 3, 4});
  ASSERT_EQ(my_vec.at(3), std_vec.at(3));
}

TEST(VectorSuite, index_empty) {
  s21::Vector<int> my_vec;
  ASSERT_THROW(my_vec[0], std::out_of_range);
}

TEST(VectorSuite, index_out_if_boundes) {
  s21::Vector<int> my_vec(4);
  ASSERT_THROW(my_vec[10], std::out_of_range);
}

TEST(VectorSuite, index) {
  s21::Vector<int> my_vec({1, 2, 3, 4});
  std::vector<int> std_vec({1, 2, 3, 4});
  ASSERT_EQ(my_vec[3], std_vec[3]);
}

TEST(VectorSuite, front_empty) {
  s21::Vector<int> my_vec;
  ASSERT_THROW(my_vec.front(), std::out_of_range);
}

TEST(VectorSuite, back_empty) {
  s21::Vector<int> my_vec;
  ASSERT_THROW(my_vec.back(), std::out_of_range);
}

TEST(VectorSuite, front_back) {
  s21::Vector<int> my_vec({1, 2, 3, 4});
  std::vector<int> std_vec({1, 2, 3, 4});
  ASSERT_EQ(my_vec.front(), std_vec.front());
  ASSERT_EQ(my_vec.back(), std_vec.back());
}

TEST(VectorSuite, empty_data) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  ASSERT_EQ(my_vec.data(), std_vec.data());
}

TEST(VectorSuite, data) {
  s21::Vector<int> my_vec({1, 2, 3});
  std::vector<int> std_vec({1, 2, 3});
  ASSERT_EQ(my_vec.data()[0], std_vec.data()[0]);
  ASSERT_EQ(my_vec.data()[1], std_vec.data()[1]);
  ASSERT_EQ(my_vec.data()[2], std_vec.data()[2]);
}

TEST(VectorSuite, empty_begin_end) {
  s21::Vector<int> my_vec;
  ASSERT_EQ(my_vec.begin(), nullptr);
  ASSERT_EQ(my_vec.end(), nullptr);
}

TEST(VectorSuite, begin_end) {
  s21::Vector<int> my_vec({1, 2, 3});
  std::vector<int> std_vec({1, 2, 3});
  ASSERT_EQ(*my_vec.begin(), *std_vec.begin());
  ASSERT_EQ(*(my_vec.end() - 1), *(std_vec.end() - 1));
}

TEST(VectorSuite, empty) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  ASSERT_EQ(my_vec.empty(), std_vec.empty());
  my_vec.push_back(1);
  std_vec.push_back(1);
  ASSERT_EQ(my_vec.empty(), std_vec.empty());
  my_vec.pop_back();
  std_vec.pop_back();
  ASSERT_EQ(my_vec.empty(), std_vec.empty());
  my_vec.push_back(1);
  std_vec.push_back(1);
  ASSERT_EQ(my_vec.empty(), std_vec.empty());
  my_vec.clear();
  std_vec.clear();
  ASSERT_EQ(my_vec.empty(), std_vec.empty());
}

TEST(VectorSuite, size) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  ASSERT_EQ(my_vec.size(), std_vec.size());
  my_vec.push_back(1);
  std_vec.push_back(1);
  ASSERT_EQ(my_vec.size(), std_vec.size());
  my_vec.insert(my_vec.begin(), 3);
  std_vec.insert(std_vec.begin(), 3);
  ASSERT_EQ(my_vec.size(), std_vec.size());
  my_vec.pop_back();
  std_vec.pop_back();
  ASSERT_EQ(my_vec.size(), std_vec.size());
  my_vec.clear();
  std_vec.clear();
  ASSERT_EQ(my_vec.size(), std_vec.size());
}

TEST(VectorSuite, max_size_1) {
  s21::Vector<int> my_vec;
  ASSERT_EQ(my_vec.max_size(), s21::Vector<int>::size_type(-1) / sizeof(int));
}

TEST(VectorSuite, max_size_2) {
  s21::Vector<long double> my_vec;
  ASSERT_EQ(my_vec.max_size(),
            s21::Vector<long double>::size_type(-1) / sizeof(long double));
}

TEST(VectorSuite, capacity) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  ASSERT_EQ(my_vec.capacity(), std_vec.capacity());
  my_vec.push_back(1);
  std_vec.push_back(1);
  ASSERT_EQ(my_vec.capacity(), std_vec.capacity());
  my_vec.insert(my_vec.begin(), 3);
  std_vec.insert(std_vec.begin(), 3);
  ASSERT_EQ(my_vec.capacity(), std_vec.capacity());
  my_vec.pop_back();
  std_vec.pop_back();
  ASSERT_EQ(my_vec.capacity(), std_vec.capacity());
  my_vec.clear();
  std_vec.clear();
  ASSERT_EQ(my_vec.capacity(), std_vec.capacity());
}

TEST(VectorSuite, reserve) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.reserve(10);
  std_vec.reserve(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.reserve(4);
  std_vec.reserve(4);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.reserve(16);
  std_vec.reserve(16);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.reserve(0);
  std_vec.reserve(0);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.reserve(100);
  std_vec.reserve(100);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, shrink_to_fit) {
  s21::Vector<int> my_vec({1, 2, 3});
  std::vector<int> std_vec({1, 2, 3});
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.push_back(10);
  std_vec.push_back(10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.shrink_to_fit();
  std_vec.shrink_to_fit();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.pop_back();
  std_vec.pop_back();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.shrink_to_fit();
  std_vec.shrink_to_fit();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.reserve(100);
  std_vec.reserve(100);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.shrink_to_fit();
  std_vec.shrink_to_fit();
}

TEST(VectorSuite, clear) {
  s21::Vector<int> my_vec({1, 2, 3});
  std::vector<int> std_vec({1, 2, 3});
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.clear();
  std_vec.clear();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.clear();
  std_vec.clear();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, swap) {
  s21::Vector<int> my_vec({1, 2});
  std::vector<int> std_vec({1, 2});
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  s21::Vector<int> my_res;
  std::vector<int> std_res;
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  my_res.swap(my_vec);
  std_res.swap(std_vec);
  ASSERT_TRUE(vectors_equal(std_res, my_res));
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, push_pop_empty) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  my_vec.push_back(3);
  std_vec.push_back(3);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  my_vec.pop_back();
  std_vec.pop_back();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, push_pop_back) {
  s21::Vector<int> my_vec({1, 2});
  std::vector<int> std_vec({1, 2});
  my_vec.push_back(3);
  std_vec.push_back(3);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  std_vec.pop_back();
  my_vec.pop_back();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, push_pop_sized) {
  s21::Vector<int> my_vec(10);
  std::vector<int> std_vec(10);
  my_vec.push_back(3);
  std_vec.push_back(3);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  std_vec.pop_back();
  my_vec.pop_back();
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, insert_single) {
  s21::Vector<int> my_vec({2});
  std::vector<int> std_vec({2});
  std_vec.insert(std_vec.begin(), 1);
  my_vec.insert(my_vec.begin(), 1);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, wrong_insert) {
  s21::Vector<int> my_vec({2});
  ASSERT_THROW(my_vec.insert(my_vec.begin() + 2, 1), std::out_of_range);
  ASSERT_THROW(my_vec.insert(my_vec.begin() - 1, 1), std::out_of_range);
}

TEST(VectorSuite, insert_empty) {
  s21::Vector<int> my_vec;
  std::vector<int> std_vec;
  std_vec.insert(std_vec.begin(), 10);
  my_vec.insert(my_vec.begin(), 10);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, erase_only) {
  s21::Vector<int> my_vec = {2};
  std::vector<int> std_vec = {2};
  std_vec.erase(std_vec.begin());
  my_vec.erase(my_vec.begin());
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, erase_not_only) {
  s21::Vector<int> my_vec = {3, 4, 5};
  std::vector<int> std_vec = {3, 4, 5};
  std_vec.erase(std_vec.begin());
  my_vec.erase(my_vec.begin());
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, wrong_erase) {
  s21::Vector<int> my_vec({2});
  ASSERT_THROW(my_vec.erase(my_vec.begin() + 2), std::out_of_range);
  ASSERT_THROW(my_vec.erase(my_vec.begin() - 1), std::out_of_range);
}

TEST(VectorSuite, erase_empty) {
  s21::Vector<int> my_vec;
  ASSERT_THROW(my_vec.erase(my_vec.begin()), std::out_of_range);
}

TEST(VectorSuite, special_insert_erase) {
  s21::Vector<int> my_vec = {3, 4, 5, 6, 4, 5};
  std::vector<int> std_vec = {3, 4, 5, 6, 4, 5};
  std_vec.erase(std_vec.begin() + 3);
  my_vec.erase(my_vec.begin() + 3);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  std_vec.insert(std_vec.begin() + 3, 10);
  my_vec.insert(my_vec.begin() + 3, 10);
  std_vec.insert(std_vec.begin(), 11);
  my_vec.insert(my_vec.begin(), 11);
  std_vec.insert(std_vec.begin() + 1, 12);
  my_vec.insert(my_vec.begin() + 1, 12);
  std_vec.insert(std_vec.begin() + 2, 13);
  my_vec.insert(my_vec.begin() + 2, 13);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  std_vec.erase(std_vec.begin());
  my_vec.erase(my_vec.begin());
  std_vec.erase(std_vec.begin());
  my_vec.erase(my_vec.begin());
  std_vec.erase(std_vec.end() - 1);
  my_vec.erase(my_vec.end() - 1);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
}

TEST(VectorSuite, extra_initial_list) {
  s21::Vector<int> my_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  ASSERT_THROW(my_vec.at(3), std::out_of_range);
}

TEST(VectorSuite, extra_default_constructors) {
  s21::Vector<int> my_vec(16);
  std::vector<int> std_vec(16);
  ASSERT_TRUE(vectors_equal(std_vec, my_vec));
  ASSERT_THROW(my_vec.at(30), std::out_of_range);
}
