#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>
#include "Future.h"

class ThreadPool {
public:
    explicit ThreadPool(size_t threads);
    ~ThreadPool();

    template<typename Func>
    auto Submit(Func f) -> MyFuture<decltype(f())>;

private:
    void Worker();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex mtx_;
    std::condition_variable cv_;
    bool stop_ = false;
};

template<typename Func>
auto ThreadPool::Submit(Func f) -> MyFuture<decltype(f())> {
    using R = decltype(f());

    MyPromise<R> promise;
    auto future = promise.get_future();

    {
        std::lock_guard<std::mutex> lock(mtx_);
        tasks_.emplace([f, p = std::move(promise)]() mutable {
            p.set_value(f());
        });
    }
    cv_.notify_one();

    return future;
}