#pragma once

#include <coroutine>
#include <iostream>
#include <vector>
#include <unordered_set>

template<typename T>
struct Generator {
    struct promise_type {
        T current_value;

        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        Generator get_return_object() {
            return Generator{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    bool next() {
        if (!handle.done()) {
            handle.resume();
        }
        return !handle.done();
    }

    T value() const {
        return handle.promise().current_value;
    }
};