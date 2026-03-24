#include <gtest/gtest.h>
#include "ThreadPool.h"
#include "ProcessPool.h"


TEST(ThreadPoolTest, BasicTasks) {
    ThreadPool pool(4);

    auto f1 = pool.Submit([] {
        return 2 + 2;
    });

    auto f2 = pool.Submit([] {
        return 10;
    });

    EXPECT_EQ(f1.get(), 4);
    EXPECT_EQ(f2.get(), 10);
}

TEST(ThreadPoolTest, MultipleTasks) {
    ThreadPool pool(2);

    auto f1 = pool.Submit([] { return 1; });
    auto f2 = pool.Submit([] { return 2; });
    auto f3 = pool.Submit([] { return 3; });

    EXPECT_EQ(f1.get(), 1);
    EXPECT_EQ(f2.get(), 2);
    EXPECT_EQ(f3.get(), 3);
}


TEST(ProcessPoolTest, BasicTasks) {
    ProcessPool pool(2);

    auto f1 = pool.Submit([] { return 5; });
    auto f2 = pool.Submit([] { return 7; });

    EXPECT_EQ(f1.get(), 5);
    EXPECT_EQ(f2.get(), 7);
}

TEST(ProcessPoolTest, MultipleTasks) {
    ProcessPool pool(3);

    auto f1 = pool.Submit([] { return 10; });
    auto f2 = pool.Submit([] { return 20; });
    auto f3 = pool.Submit([] { return 30; });

    EXPECT_EQ(f1.get(), 10);
    EXPECT_EQ(f2.get(), 20);
    EXPECT_EQ(f3.get(), 30);
}