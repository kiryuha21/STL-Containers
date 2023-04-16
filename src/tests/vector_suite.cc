#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool vectors_equal(const std::vector<T> &std_res,
                   const s21::Vector<T> &my_res) {
  if (my_res.size() != std_res.size()) {
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
}  // namespace s21
