#pragma once
#include <mutex>
#include <condition_variable>
#include <optional>
#include <stdexcept>

template<typename T>
class SharedState {
public:
    void set_value(T v) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            value_ = std::move(v);
            ready_ = true;
        }
        cv_.notify_all();
    }

    T get() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [&]{ return ready_; });
        return *value_;
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    std::optional<T> value_;
    bool ready_ = false;
};

template<typename T>
class MyFuture {
public:
    explicit MyFuture(std::shared_ptr<SharedState<T>> state)
        : state_(std::move(state)) {}

    T get() {
        if (!state_) {
            throw std::runtime_error("No state");
        }
        return state_->get();
    }

private:
    std::shared_ptr<SharedState<T>> state_;
};

template<typename T>
class MyPromise {
public:
    MyPromise() : state_(std::make_shared<SharedState<T>>()) {}

    MyFuture<T> get_future() {
        return MyFuture<T>(state_);
    }

    void set_value(T value) {
        state_->set_value(std::move(value));
    }

private:
    std::shared_ptr<SharedState<T>> state_;
};