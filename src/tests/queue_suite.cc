// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool queues_equal(queue<T> first, queue<T> second) {
  while (!first.empty() && !second.empty()) {
    T first_elem = first.front();
    T second_elem = second.front();

    T first_copy = first_elem;
    T second_copy = second_elem;
    if (first_copy != second_copy) {
      return false;
    }

    first.pop();
    second.pop();
  }

  return first.empty() && second.empty();
}

template <class T>
bool queues_equal(queue<T> first, std::queue<T> second) {
  while (!first.empty() && !second.empty()) {
    T first_elem = first.front();
    T second_elem = second.front();

    T first_copy = first_elem;
    T second_copy = second_elem;
    if (first_copy != second_copy) {
      return false;
    }

    first.pop();
    second.pop();
  }

  return first.empty() && second.empty();
}

TEST(QueueSuite, default_constructor_test) {
  std::queue<int> std_queue;
  queue<int> my_queue;

  ASSERT_TRUE(my_queue.empty());
  ASSERT_EQ(my_queue.empty(), std_queue.empty());

  ASSERT_EQ(std_queue.size(), 0);
  ASSERT_EQ(std_queue.size(), my_queue.size());

  ASSERT_THROW(my_queue.front(), std::logic_error);
  ASSERT_THROW(my_queue.back(), std::logic_error);
}

TEST(QueueSuite, initializer_constructor_test) {
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);

  queue<int> my_queue = {1, 2, 3};

  ASSERT_EQ(my_queue.front(), 1);
  ASSERT_EQ(std_queue.front(), my_queue.front());

  ASSERT_EQ(my_queue.back(), 3);
  ASSERT_EQ(std_queue.back(), my_queue.back());

  std_queue.pop();
  my_queue.pop();

  ASSERT_EQ(my_queue.front(), 2);
  ASSERT_EQ(std_queue.front(), my_queue.front());
}

TEST(QueueSuite, copy_constructor_test) {
  std::queue<int> std_base;
  std_base.push(1);
  std_base.push(2);
  std_base.push(3);
  std::queue<int> std_res(std_base);

  queue<int> my_base = {1, 2, 3};
  queue<int> my_res(my_base);

  ASSERT_TRUE(queues_equal(my_base, my_res));
  ASSERT_TRUE(queues_equal(my_res, std_res));
  ASSERT_EQ(my_res.front(), std_res.front());
  ASSERT_EQ(my_res.back(), std_res.back());
}

TEST(QueueSuite, move_constructor_test) {
  std::queue<int> std_base;
  std_base.push(1);
  std_base.push(2);
  std_base.push(3);
  std::queue<int> std_res(std::move(std_base));

  queue<int> my_base = {1, 2, 3};
  queue<int> my_res(std::move(my_base));

  ASSERT_TRUE(my_base.empty());
  ASSERT_TRUE(queues_equal(my_res, std_res));
  ASSERT_EQ(my_res.front(), std_res.front());
  ASSERT_EQ(my_res.back(), std_res.back());
}

TEST(QueueSuite, present_front_test) {
  queue<int> my_queue = {1, 2};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);

  ASSERT_EQ(my_queue.front(), 1);
  ASSERT_EQ(my_queue.front(), std_queue.front());
}

TEST(QueueSuite, missing_front_test) {
  queue<int> my_queue;
  ASSERT_THROW(my_queue.front(), std::logic_error);
}

TEST(QueueSuite, present_back_test) {
  queue<int> my_queue = {1, 2};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);

  ASSERT_EQ(my_queue.back(), 2);
  ASSERT_EQ(my_queue.back(), std_queue.back());
}

TEST(QueueSuite, missing_back_test) {
  queue<int> my_queue;
  ASSERT_THROW(my_queue.back(), std::logic_error);
}

TEST(QueueSuite, empty_queue_test) {
  queue<int> my_queue;
  std::queue<int> std_queue;

  ASSERT_TRUE(my_queue.empty());
  ASSERT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueSuite, non_empty_queue_test) {
  queue<int> my_queue = {1};
  std::queue<int> std_queue;
  std_queue.push(1);

  ASSERT_FALSE(my_queue.empty());
  ASSERT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueSuite, non_zero_size_test) {
  queue<int> my_queue = {1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);

  ASSERT_EQ(my_queue.size(), 3);
  ASSERT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueSuite, zero_size_test) {
  queue<int> my_queue;
  std::queue<int> std_queue;

  ASSERT_EQ(my_queue.size(), 0);
  ASSERT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueSuite, push_to_empty_test) {
  queue<int> my_queue;
  std::queue<int> std_queue;

  ASSERT_THROW(my_queue.back(), std::logic_error);
  ASSERT_THROW(my_queue.front(), std::logic_error);

  my_queue.push(1);
  std_queue.push(1);

  ASSERT_EQ(my_queue.size(), 1);
  ASSERT_EQ(my_queue.front(), 1);
  ASSERT_EQ(my_queue.front(), my_queue.back());
  ASSERT_EQ(my_queue.front(), std_queue.front());
  ASSERT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueSuite, push_to_non_empty_test) {
  queue<int> my_queue = {1};
  std::queue<int> std_queue;
  std_queue.push(1);

  my_queue.push(2);
  std_queue.push(2);

  ASSERT_EQ(my_queue.size(), 2);
  ASSERT_EQ(my_queue.front(), 1);
  ASSERT_EQ(my_queue.back(), 2);
  ASSERT_EQ(my_queue.back(), std_queue.back());
  ASSERT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueSuite, pop_non_empty_test) {
  queue<int> my_queue = {1, 2};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);

  ASSERT_EQ(my_queue.front(), 1);
  ASSERT_EQ(my_queue.front(), std_queue.front());

  my_queue.pop();
  std_queue.pop();

  ASSERT_EQ(my_queue.size(), 1);
  ASSERT_EQ(my_queue.front(), 2);
  ASSERT_EQ(my_queue.front(), std_queue.front());
  ASSERT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueSuite, pop_empty_test) {
  queue<int> my_queue;
  ASSERT_THROW(my_queue.pop(), std::logic_error);
}

TEST(QueueSuite, swap_test) {
  queue<int> first_queue = {1, 2, 3};
  queue<int> second_queue = {4, 5, 6};
  queue<int> first_copy(first_queue);
  queue<int> second_copy(second_queue);

  first_queue.swap(second_queue);
  ASSERT_TRUE(queues_equal(first_queue, second_copy));
  ASSERT_TRUE(queues_equal(second_queue, first_copy));
}

}  // namespace s21
