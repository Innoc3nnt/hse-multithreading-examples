#include <gtest/gtest.h>
#include <vector>
#include "ApplyFunction.h"

TEST(ApplyFunctionTest, SingleThread) {
    std::vector<int> data = {1, 2, 3, 4};

    ApplyFunction<int>(data, [](int& x) { x *= 2; }, 1);

    EXPECT_EQ(data, std::vector<int>({2, 4, 6, 8}));
}

TEST(ApplyFunctionTest, MultiThread) {
    std::vector<int> data = {1, 2, 3, 4, 5, 6};

    ApplyFunction<int>(data, [](int& x) { x += 1; }, 3);

    EXPECT_EQ(data, std::vector<int>({2, 3, 4, 5, 6, 7}));
}

TEST(ApplyFunctionTest, MoreThreadsThanElements) {
    std::vector<int> data = {1, 2, 3};

    ApplyFunction<int>(data, [](int& x) { x *= x; }, 10);

    EXPECT_EQ(data, std::vector<int>({1, 4, 9}));
}

TEST(ApplyFunctionTest, EmptyVector) {
    std::vector<int> data;

    ApplyFunction<int>(data, [](int& x) { x += 1; }, 4);

    EXPECT_TRUE(data.empty());
}

TEST(ApplyFunctionTest, HeavyFunctionCorrectness) {
    std::vector<int> data(1000, 1);

    ApplyFunction<int>(data, [](int& x) {
        for (int i = 0; i < 1000; ++i) x += 1;
    }, 4);

    for (auto x : data) {
        EXPECT_EQ(x, 1001);
    }
}