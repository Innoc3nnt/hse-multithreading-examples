#pragma once

#include <optional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

template <class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size)
        : capacity(size), closed(false) {}

    void Send(const T& value) {
        std::unique_lock<std::mutex> lock(mtx);

        not_full.wait(lock, [&]() {
            return queue.size() < capacity || closed;
        });

        if (closed) {
            throw std::runtime_error("Channel is closed");
        }

        queue.push(value);
        not_empty.notify_one();
    }

    std::optional<T> Recv() {
        std::unique_lock<std::mutex> lock(mtx);

        not_empty.wait(lock, [&]() {
            return !queue.empty() || closed;
        });

        if (queue.empty()) {
            return std::nullopt;
        }

        T value = std::move(queue.front());
        queue.pop();

        not_full.notify_one();

        return value;
    }

    void Close() {
        std::unique_lock<std::mutex> lock(mtx);
        closed = true;
        not_empty.notify_all();
        not_full.notify_all();
    }

private:
    int capacity;
    std::queue<T> queue;
    bool closed;

    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;
};