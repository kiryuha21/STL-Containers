#include <gtest/gtest.h>
#include <queue>

#include "../s21_containers.h"

namespace s21 {
    TEST(QueueSuite, default_constructor) {
        std::queue<int> a;
        Queue<int> b;
        ASSERT_EQ(a.size(), b.size());
    }
}