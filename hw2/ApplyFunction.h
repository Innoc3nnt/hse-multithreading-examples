#include <vector>
#include <functional>
#include <thread>

template <typename T>
void ApplyFunction(std::vector<T>& data, const std::function<void(T&)>& transform, const int threadCount = 1) {
    if (data.empty()) return;

    int threads = std::min<int>(threadCount, data.size());
    if (threads <= 1) {
        for (auto& el : data) {
            transform(el);
        }
        return;
    }

    std::vector<std::thread> workers;
    size_t chunk = data.size() / threads;
    size_t remainder = data.size() % threads;

    size_t start = 0;

    for (int i = 0; i < threads; ++i) {
        size_t end = start + chunk + (i < remainder ? 1 : 0);

        workers.emplace_back([start, end, &data, &transform]() {
            for (size_t j = start; j < end; ++j) {
                transform(data[j]);
            }
        });

        start = end;
    }

    for (auto& t : workers) {
        t.join();
    }
}